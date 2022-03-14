package model;

import utils.SegmentArrayManager;
import view.MyFrame;

import javax.swing.*;
import java.io.*;

/** éditeur pour générer les événements d'une forme lisibles par un e-puck 2 en line-follower */

public class Main {
	public static int[][] segments = new int[100][4];
	public static MyFrame myFrame;

	public static void main(String[] args) {
		myFrame = new MyFrame();
		myFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		myFrame.setVisible(true);

		SwingUtilities.invokeLater(() -> {
			SegmentArrayManager.setInitialPosition(myFrame.canvas.getWidth() / 2, myFrame.canvas.getHeight() / 2);

		});
	}

	public static int[][] getSegments() {
		return segments;
	}

}