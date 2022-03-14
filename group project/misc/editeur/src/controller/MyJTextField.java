package controller;

import utils.EventsArrayManager;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MyJTextField extends JTextField {
	final String initialText;

	public MyJTextField(String text) {
		super(text);
		initialText = text;
		setMaximumSize(new Dimension(1000,30));

		this.addMouseListener(new MouseListener() {
			boolean firstClick;
			@Override
			public void mouseClicked(MouseEvent e) {
				firstClick = true;
				if (getText().equals(initialText)) {
					setText("");
				}
			}

			@Override
			public void mousePressed(MouseEvent e) {

			}

			@Override
			public void mouseReleased(MouseEvent e) {

			}

			@Override
			public void mouseEntered(MouseEvent e) {
				setBackground(Color.WHITE);
				if (getText().equals(initialText) && firstClick) {
					setText("");
				}
			}

			@Override
			public void mouseExited(MouseEvent e) {
				if (getText().equals("")) {
					setText(initialText);
				}
			}
		});

		this.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String name = getText();
				if (name.equals("") || name.equals(initialText)) setBackground(Color.RED);
				else EventsArrayManager.generateEventsForLineFollowing(name);
			}
		});
	}
}
