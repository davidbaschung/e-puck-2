package controller;

import model.Main;
import utils.SegmentArrayManager;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RemoveButtonListener implements ActionListener {
	@Override
	public void actionPerformed(ActionEvent e) {
		SegmentArrayManager.remove(Main.segments);
		Main.myFrame.canvas.update(Main.myFrame.canvas.getGraphics());
	}
}
