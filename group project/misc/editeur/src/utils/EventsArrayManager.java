package utils;

		import model.Main;

		import java.io.IOException;

public class EventsArrayManager {
	// NOTE : E-puck 2 specifications. Units : centimeter and seconds.
	private static final double eDiameter = 7.1, eWheelDiameter = 4.1, eAxleTrack = 5.3 , eMaxSteps = 1200, eStepsPerRev = 20;
	private static final double eWheelPerimeter = Math.PI * eWheelDiameter/* ~12.4 */;
	private final double eMaxSpeed = eMaxSteps/1000*eWheelPerimeter/* ~15.4 */;

	static int standardSpeed = 200;
	static int rotationSpeed = 200;
	static double normDistance = ((double) standardSpeed)/1000*eWheelPerimeter;
	static double rotationDistance = ((double)rotationSpeed)/1000*eWheelPerimeter;
	static double wallFollowOffset = 1;
	static double blockLength = SegmentArrayManager.blockLength, blockWidth = SegmentArrayManager.blockWidth, blockHeight = SegmentArrayManager.blockHeight;

	// NOTE : events structure : 1.line(=0) / (curve angle) 2.block(=1)/joint 3.time 4.distance 5.left wheel (cm/s) 6.right wheel (cm/s)


	public static void generateEventsForLineFollowing(String shapeName) {

		String fileName = CSVIO.path+"line/"+shapeName+".csv";

		int[][] trigoSegments = SegmentArrayManager.getTrigonometricSegments(Main.segments);
		int size = SegmentArrayManager.getSize(trigoSegments);
		if (size==0) return;

		double[][] events = new double[4*size][6];
		events[0] = new double[]{0, 1, blockLength / normDistance, blockLength, normDistance, normDistance};
		int nextSegmentIndex;
		for (int i=0; i<size; i++) {
			if (i<size-1) nextSegmentIndex = i+1;
			else nextSegmentIndex=0;
			addCentralJointAndNextBlock(events, trigoSegments, i, nextSegmentIndex);
		}

		try {
			CSVIO.writeCSV("segment angle (rad),along block,time (s),central distance (cm/s),left wheel (cm/s),right wheel (cm/s)",events, fileName); //TODO all filenames
		} catch (IOException e) {
			e.printStackTrace();
		}

		System.out.println("just saved the list : ");
		printListBeginning(events);

	}

	private static void addCentralJointAndNextBlock(double[][] events, int[][] segments, int indexA, int indexB) {

		double deltaAngle = SegmentArrayManager.computeDeltaAngle(segments[indexA], segments[indexB]);
		events[getSize(events)] = new double[] {deltaAngle, 0, Math.abs(deltaAngle)*(eDiameter/2) / normDistance, 0, deltaAngle>0?-rotationDistance : rotationDistance, deltaAngle>0? rotationDistance :-rotationDistance};
		double length = SegmentArrayManager.blockLength;
		events[(indexB!=0)?getSize(events):0] = new double[] {0,1, blockLength / normDistance, blockLength, normDistance, normDistance};

	}

	public static void generateEventsForWallFollowing(String shapeName) {

		String fileName = CSVIO.path+"wall/"+shapeName+".csv";

		int[][] trigoSegments = SegmentArrayManager.getTrigonometricSegments(Main.segments);
		int size = SegmentArrayManager.getSize(trigoSegments);
		if (size==0) return;

		double sum = SegmentArrayManager.sumDeltaAngles(trigoSegments);
		double[][] events = new double[4*size][6];
		events[0] = new double[]{0, 1, blockLength / normDistance, blockLength, normDistance, normDistance};
		int nextSegmentIndex;
		for (int i=0; i<size; i++) {
			if (i<size-1) nextSegmentIndex = i+1;
			else nextSegmentIndex=0;
			if (sum>0) addRightSideJointEventsAndNextBlock(events, trigoSegments, i, nextSegmentIndex, wallFollowOffset);
			else if (sum<0) addLeftSideJointEventsAndNextBlock(events, trigoSegments, i, nextSegmentIndex, wallFollowOffset);
		}

		try {
			CSVIO.writeCSV("segment angle (rad),along block,time (s),central distance (cm/s),left wheel (cm/s),right wheel (cm/s)",events, fileName); //TODO all filenames
		} catch (IOException e) {
			e.printStackTrace();
		}

		System.out.println("just saved the list : ");
		printListBeginning(events);

	}

	public static double[][] loadEvents(String fileName) {
		double events[][] = null;
		try {
			events = CSVIO.readCSV("data/events.csv");
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("loaded the list :");
		System.out.println(EventsArrayManager.getSize(events));
		printListBeginning(events);
		return events;
	}

	private static void addLeftSideJointEventsAndNextBlock(double[][] events, int[][] segments, int indexA, int indexB, double offset) {
		addSideJointEvents(events,segments,indexA,indexB,offset,true);
	}
	private static void addRightSideJointEventsAndNextBlock(double[][] events, int[][] segments, int indexA, int indexB, double offset) {
		addSideJointEvents(events,segments,indexA,indexB,offset,false);
	}
	private static void addSideJointEvents(double[][] events, int[][] segments, int indexA, int indexB, double offset, boolean left) {

		double angle = SegmentArrayManager.computeDeltaAngle(segments[indexA], segments[indexB]);
		SegmentArrayManager.computeDeltaAngle(segments[indexA], segments[indexB]);
		if ((angle>0 && left) || (angle<0 && ! left)) createInternalJoint(events,segments,indexA,indexB,offset);
		if ((angle>0 && ! left) || (angle<0 && left)) createExternalJoint(events,segments,indexA,indexB,offset);
		if (angle==0) {
			double jointVectorLength = blockWidth/2;//Math.sqrt(Math.pow(jointVector[0],2) + Math.pow(jointVector[1],2)) / SegmentArrayManager.canvasDotsPerCentimeter;
			events[getSize(events)] = new double[] {0,0, jointVectorLength / normDistance, jointVectorLength, normDistance, normDistance};
			//TODO offset & joint si <90°
		}
	}

	private static void createInternalJoint(double[][] events, int[][] segments, int indexA, int indexB, double offset) {
		double deltaAngle = SegmentArrayManager.computeDeltaAngle(segments[indexA], segments[indexB]);
		double segmentVectorLengthA = /*(indexA!=0)?*/(events[getSize(events)-1][3])/*:blockLength*/ - (offset+eDiameter/2)*Math.abs(Math.atan(deltaAngle/2));
		events[getSize(events)-1] = new double[] {0,1, segmentVectorLengthA / normDistance, segmentVectorLengthA, normDistance, normDistance};
		events[getSize(events)] = new double[] {deltaAngle, 0, Math.abs(deltaAngle)*(eDiameter/2) / normDistance, 0, deltaAngle>0?-rotationDistance : rotationDistance, deltaAngle>0? rotationDistance :-rotationDistance};
		double segmentVectorLengthB = ( (indexB!=0)?blockLength:events[0][3] ) - (offset+eDiameter/2)*Math.atan(deltaAngle/2);
		events[(indexB!=0)?getSize(events):0] = new double[] {0,1, segmentVectorLengthB / normDistance, segmentVectorLengthB, normDistance, normDistance};
	}
	private static void createExternalJoint(double[][] events, int[][] segments, int indexA, int indexB, double offset) {
		double deltaAngle = SegmentArrayManager.computeDeltaAngle(segments[indexA], segments[indexB]);
		int[] joint = new int[] { segments[indexA][2], segments[indexA][3], segments[indexB][0], segments[indexB][1] };
		double AtoJointDeltaAngle = SegmentArrayManager.computeDeltaAngle(segments[indexA], joint);
		double timeA = Math.abs(AtoJointDeltaAngle)*(offset+eDiameter)/normDistance;
		events[getSize(events)] = new double[] {AtoJointDeltaAngle, 0, timeA, Math.abs(AtoJointDeltaAngle)*(offset+eDiameter/2), AtoJointDeltaAngle>0?(AtoJointDeltaAngle*offset/timeA):normDistance, AtoJointDeltaAngle<0?(Math.abs(AtoJointDeltaAngle)*offset/timeA):normDistance};
		events[getSize(events)] = new double[] {0, 0, SegmentArrayManager.getSegmentLength(joint)/normDistance, SegmentArrayManager.getSegmentLength(joint), normDistance, normDistance};
		double jointToBDeltaAngle = SegmentArrayManager.computeDeltaAngle(joint,segments[indexB]);
		double timeB = Math.abs(jointToBDeltaAngle)*(offset+eDiameter)/normDistance;
		events[getSize(events)] = new double[] {jointToBDeltaAngle, 0, timeB, Math.abs(jointToBDeltaAngle)*(offset+eDiameter/2), jointToBDeltaAngle>0?(jointToBDeltaAngle*offset/timeB):normDistance, jointToBDeltaAngle<0?(Math.abs(jointToBDeltaAngle)*offset/timeB):normDistance};
		if (indexB!=0) events[getSize(events)] = new double[] {0,1, blockLength / normDistance, blockLength, normDistance, normDistance};
	}


	public static int getSize(double[][] list) {
		for (int i=0; i<list.length; i++) {
			boolean containsSomething=false;
			for (int j=0; j<list[0].length; j++) {
				if (list[i][j] != 0) {
					containsSomething = true;
				}
			}
			if ( ! containsSomething) return i;
		}
		return list.length;
	}

	public static void printListBeginning(double[][] list) {
		int size = getSize(list);
		System.out.println("printListBeginning() --------------------------");
		for (int i=0; i<size; i++) {
			System.out.println(String.format("events[%d] : [0]:%.5f [1]:%.5f [2]:%.5f [3]:%.5f [4]%.5f [5]%.5f",i,list[i][0],list[i][1],list[i][2],list[i][3],list[i][4],list[i][5]));
		}
	}

}