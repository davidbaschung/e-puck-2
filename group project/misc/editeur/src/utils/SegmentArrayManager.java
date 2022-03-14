package utils;

import model.Main;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class SegmentArrayManager {

	public static int canvasDotsPerCentimeter = 10;
	public static double blockLength = 10d, blockWidth = 1.8d, blockHeight = 5.5d;
	private static int[] initialPosition = new int[2];

	public static void add(int[][] list) {
		int index = getSize(list);
		if (index == list.length) { System.out.println("max blocks reached"); return; }
		if (index==0) {
			initialize(list);
			return;
		}

		int[] newSegment = new int[4];
		double angle = getSegmentAngle(list[index-1]);
		newSegment[0] = list[index-1][2] + (int)(blockWidth/2 * canvasDotsPerCentimeter * Math.cos(angle));
		newSegment[1] = list[index-1][3] + (int)(blockWidth/2 * canvasDotsPerCentimeter * Math.sin(angle));

		newSegment[2] = newSegment[0] + (int)(blockLength * canvasDotsPerCentimeter * Math.cos(angle));
		newSegment[3] = newSegment[1] + (int)(blockLength * canvasDotsPerCentimeter * Math.sin(angle));
		list[index] = newSegment;
//		printListBeginning(list);
	}

	private static void initialize(int[][] list) {
		int[] newSegment = new int[4];
		newSegment[0] = initialPosition[0];
		newSegment[1] = initialPosition[1];

		newSegment[2] = newSegment[0] + (int)(blockLength * canvasDotsPerCentimeter);
		newSegment[3] = newSegment[1];
		list[0] = newSegment;
	}

	public static void remove(int[][] list) {
		int size = getSize(list);
		if (size==0) return;
		int[] nullSegment = {0,0,0,0};
		list[size-1] = nullSegment;
	}

	public static int getSize(int[][] list) {
		int size=0;
		for (int i=0; i<list.length; i++) {
			if (list[i][0]==0 && list[i][1]==0 && list[i][2]==0 && list[i][3]==0) {
				size = i;
				break;
			} else size = list.length;
		}
		return size;
	}

	public static double getSegmentAngle(int[] segment) {
		double angle;
		double dx = (segment[2]-segment[0]), dy = (segment[3]-segment[1]);
		angle = Math.atan2(dy,dx);
		return angle;
	}

	public static double computeDeltaAngle(int[] segmentA, int[] segmentB) {
		double angle = getSegmentAngle(segmentB) - getSegmentAngle(segmentA);
		if (angle>Math.PI) angle-=2*Math.PI;
		if (angle<-Math.PI) angle+=2*Math.PI;
		return angle;
	}

	public static void printListBeginning(int[][] list) {
		int size = getSize(list);
		System.out.println("printListBeginning() --------------------------");
		for (int i=0; i<size; i++) {
			System.out.println(String.format("segments[%d] : [0]:%d [1]:%d [2]:%d [3]:%d",i,list[i][0],list[i][1],list[i][2],list[i][3]));
		}
	}

	public static double getSegmentLength(int[] segment) {
		int[] deltaSegment = new int[] {segment[2]-segment[0], segment[3]-segment[1]};
		return Math.sqrt(Math.pow(deltaSegment[0],2) + Math.pow(deltaSegment[1],2)) / SegmentArrayManager.canvasDotsPerCentimeter;
	}

	public static void setInitialPosition(int x, int y) {
		initialPosition[0] = x;
		initialPosition[1] = y;
	}

	public static int[][] getTrigonometricSegments(int[][] segments) {
		int[][] trigoSegments = new int[segments.length][segments[0].length];
		for (int i=0; i<segments.length; i++) {
			trigoSegments[i] = getTrigonometricSegment(segments[i]);
		}
		return trigoSegments;
	}

	public static int[] getTrigonometricSegment(int[] segment) {
		int[] trigoSegment = new int[4];
		trigoSegment[0] = segment[0];
		trigoSegment[1] = - segment[1];
		trigoSegment[2] = segment[2];
		trigoSegment[3] = - segment[3];
		return trigoSegment;
	}

	public static double sumDeltaAngles(int[][] trigoSegments) {
		double sum=0;
		for (int i=0; i<trigoSegments.length; i++) {
			sum += computeDeltaAngle(trigoSegments[i],trigoSegments[(i!=trigoSegments.length-1)?(i+1):0]);
		}
		return sum;
	}

//	static int[][] readSegments(String fileName) throws IOException {
//		int[][] segments=new int[100][4];
//		try (BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName))) {
//			String line = new String();
//			int i = 0;
//			outerloop:
//			while ((line = bufferedReader.readLine()) != null) {
//				int j = 0, wordCount = 0;
//				int[] values = new int[4];
//				String word = new String();
//				char c = 'z';
//				while (j <= line.length()) {
//					if (j < line.length()) c = line.charAt(j);
//					else c = '\n';
//
//					if (c == ',' || c == '\n') {
//						values[wordCount] = Integer.parseInt(word);
//						word = new String();
//						wordCount++;
//
//					} else if (c >= 48 && c <= 57) {
//						word += c;
//					} else {
////						i++;
//						continue outerloop;
//					}
//					j++;
//				}
//				segments[i] = values;
//				i++;
//			}
//
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//		return segments;
//	}
//
//	public static void writeSegments(int[][] segments, String fileName) throws IOException {
//		try (FileWriter fileWriter = new FileWriter(fileName)) {
//			int i = 0;
//			while (!(segments[i][0] == 0 && segments[i][1] == 0 && segments[i][2] == 0 && segments[i][3] == 0)) {
//				int j = 0;
//				String line = new String();
//				while (j < segments[0].length) {
//					line += segments[i][j];
//					if (!(j == segments[0].length - 1))
//						line += ',';
//					else line += '\n';
//					j++;
//				}
//				i++;
//				fileWriter.write(line);
//			}
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//	}
}
