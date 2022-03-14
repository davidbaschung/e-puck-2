package view;

import controller.*;

import javax.swing.*;
import java.awt.*;

public class MyFrame extends JFrame {
	public MyCanvas canvas;

	public MyFrame() throws HeadlessException {
		BorderLayout layout = new BorderLayout();
		setTitle("Robotics, Part 2, Projcet - Polygon Editor - Group 6, David Baschung, Samuel Neu, Vladislav Shylin");

		Dimension realDimension = Toolkit.getDefaultToolkit().getScreenSize();
		Rectangle effectiveRectangle = GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds();
		Dimension effectiveDimension = new Dimension(effectiveRectangle.width, effectiveRectangle.height);
		setSize(effectiveDimension);

		JPanel sidePanel = new JPanel();
		BoxLayout boxLayout = new BoxLayout(sidePanel, BoxLayout.Y_AXIS);
		sidePanel.setLayout(boxLayout);
		JButton addButton = new JButton("<html><div style=\"font-style:bold;font-size:30;width:100%;float:center;text-align:center\">add<br/>segment</div></html>");
		addButton.setMaximumSize(new Dimension(1000,200));
		addButton.addActionListener(new AddButtonListener());
		sidePanel.add(addButton);
		JButton removeButton = new JButton("<html><div style=\"font-style:bold;font-size:30;width:100%;float:center;text-align:center\">remove<br/>segment</div></html>");
		removeButton.setMaximumSize(new Dimension(1000,200));
		removeButton.setSize(sidePanel.getWidth(), sidePanel.getWidth());
		removeButton.addActionListener(new RemoveButtonListener());
		sidePanel.add(removeButton);
		JLabel myLabel = new JLabel("<html><div style=\"font-style:bold;font-size:20;width:100%;text-align:justify;margin:15\">Click on the canvas to<br/>direct last segment</div></html>");
		sidePanel.add(myLabel);
		MyJTextField jTextField = new MyJTextField("Shape name");
		sidePanel.add(jTextField);
		JButton generateButton = new JButton("<html><div style=\"font-style:bold;font-size:20;width:100%;text-align:justify;margin:15\">Generate signature</div></html>");
		generateButton.addActionListener(new GenerateButtonListener(jTextField));
		generateButton.setSize(sidePanel.getWidth(), sidePanel.getWidth());
		sidePanel.add(generateButton);
		add(sidePanel, BorderLayout.WEST);

		canvas = new MyCanvas();
		canvas.setSize(new Dimension(1000, 300));
		canvas.setBackground(Color.LIGHT_GRAY);
		add(canvas, BorderLayout.CENTER);
	}

	@Override
	public void update(Graphics g) {
		super.update(g);
		canvas.update(g);
	}
}