package controller;

import utils.EventsArrayManager;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GenerateButtonListener implements ActionListener {
	private final MyJTextField jTextField;

	public GenerateButtonListener(MyJTextField jTextField) {
		this.jTextField = jTextField;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String name = jTextField.getText();
		if (name.equals("") || name.equals(jTextField.initialText)) jTextField.setBackground(Color.RED);
		else EventsArrayManager.generateEventsForLineFollowing(name);
	}
}
