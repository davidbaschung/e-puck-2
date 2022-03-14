package controller;

import model.Main;
import utils.SegmentArrayManager;
import view.MyCanvas;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class CanvasMouseListener implements MouseListener {
	private MyCanvas canvas;

	public CanvasMouseListener(MyCanvas canvas) {
		this.canvas = canvas;
	}

	@Override
	public void mouseClicked(MouseEvent e) {

	}

	@Override
	public void mousePressed(MouseEvent e) {
		int size = SegmentArrayManager.getSize(Main.segments);
		if (size == 0) return;

		int[] currentSegment = Main.segments[size - 1];
		int[] previousSegment;
		if (size >= 2) {
			previousSegment = Main.segments[size-2];
		} else {
			previousSegment = new int[] {0, 0, canvas.getWidth()/2, canvas.getHeight()/2};
		}

		int dxMouse = e.getX() - previousSegment[2], dyMouse = e.getY() - previousSegment[3];
		double currentAngle =  Math.atan2(dyMouse,dxMouse);
		int[] mouseVector = new int[] {0,0,dxMouse,dyMouse};
		double previousAngle = SegmentArrayManager.getSegmentAngle(previousSegment);
		double deltaAngle = SegmentArrayManager.computeDeltaAngle(previousSegment, mouseVector);

		currentSegment[0] = (int) (previousSegment[2] + SegmentArrayManager.canvasDotsPerCentimeter * SegmentArrayManager.blockWidth/(Math.abs(deltaAngle)>(Math.PI/2)?1:2) * Math.cos(previousAngle+deltaAngle/2));
		currentSegment[1] = (int) (previousSegment[3] + SegmentArrayManager.canvasDotsPerCentimeter * SegmentArrayManager.blockWidth/(Math.abs(deltaAngle)>(Math.PI/2)?1:2) * Math.sin(previousAngle+deltaAngle/2));
		currentSegment[2] = (int) (currentSegment[0] + SegmentArrayManager.canvasDotsPerCentimeter * ( SegmentArrayManager.blockWidth/(Math.abs(deltaAngle)>(Math.PI/2)?1:2) * Math.cos(previousAngle+deltaAngle/2) + SegmentArrayManager.blockLength *  Math.cos(currentAngle)) );
		currentSegment[3] = (int) (currentSegment[1] + SegmentArrayManager.canvasDotsPerCentimeter * ( SegmentArrayManager.blockWidth/(Math.abs(deltaAngle)>(Math.PI/2)?1:2) * Math.sin(previousAngle+deltaAngle/2) + SegmentArrayManager.blockLength *  Math.sin(currentAngle)) );
		canvas.update(canvas.getGraphics());
	}

	@Override
	public void mouseReleased(MouseEvent e) {

	}

	@Override
	public void mouseEntered(MouseEvent e) {

	}

	@Override
	public void mouseExited(MouseEvent e) {

	}
}
