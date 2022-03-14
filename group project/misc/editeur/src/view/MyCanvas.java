package view;

import controller.CanvasMouseListener;
import model.Main;
import utils.SegmentArrayManager;

import javax.swing.*;
import java.awt.*;

public class MyCanvas extends JPanel {

	public MyCanvas() {
		addMouseListener(new CanvasMouseListener(this));
	}

	@Override
	public void paint(Graphics g) {
		super.paint(g);
		drawLines(g);
	}

	private void drawLines(Graphics g) {
		int[][] segments = Main.getSegments();
		Graphics2D graphics2D = (Graphics2D) g.create();
		graphics2D.setStroke(new BasicStroke(3, BasicStroke.CAP_ROUND,BasicStroke.JOIN_ROUND));
		for (int i=0; i<segments.length; i++) {
			if (segments[i][0] != 0 && segments[i][1] != 0 && segments[i][2] != 0 && segments[i][3]!=0)
				graphics2D.drawLine(segments[i][0], segments[i][1], segments[i][2], segments[i][3]);
			else break;
		}
		graphics2D.dispose();
	}

	@Override
	public Point getMousePosition() throws HeadlessException {
		return super.getMousePosition();
	}
}
