package controller;

import model.Main;
import utils.SegmentArrayManager;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddButtonListener implements ActionListener {
	@Override
	public void actionPerformed(ActionEvent e) {
		SegmentArrayManager.add(Main.segments);
		Main.myFrame.canvas.update(Main.myFrame.canvas.getGraphics());
	}
}
