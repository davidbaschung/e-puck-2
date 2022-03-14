package utils;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class CSVIO {

	static String path = "data/";

	/** lire un fichier CSV contenant des événements */

	public static double[][] readCSV(String fileName) throws IOException {
		return readCSV(fileName,-1);
	}
	public static double[][] readCSV(String fileName, int arraySize) throws IOException {
		double[][] list = null;
		BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName));
		try {
			String titleLine = bufferedReader.readLine();
			int sizeCounter=0;
			for (int i=0; i<titleLine.length(); i++) {
				char c = titleLine.charAt(i);
				if (c == ',' || i==titleLine.length()-1) sizeCounter++;
			}
			if (arraySize==-1) {arraySize = (int) Math.pow(2,20);}
			else arraySize = 400;
			list = new double[arraySize][sizeCounter];
			String line = new String();
			int i = 0;
			outerloop:
			while ((line = bufferedReader.readLine()) != null) {
				int j = 0, wordCount = 0;
				double[] values = new double[sizeCounter];
				String word = new String();
				char c = 'z';
				while (j <= line.length()) {
					if (j < line.length()) c = line.charAt(j);
					else c = '\n';

					if (c == ',' || c == '\n') {
						values[wordCount] = Double.parseDouble(word);
						word = new String();
						wordCount++;

					} else if (c >= 48 && c <= 57 || c == '.' || c == '-') {
						word += c;
					} else {
						continue outerloop;
					}
					j++;
				}
				list[i] = values;
				i++;
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			bufferedReader.close();
		}
		return list;
	}

	/** écrire un fichier CSV contenant des événements */
	/** la sortie est prévue dans ./data/line/ */

	public static void writeCSV(String titleLine, double[][] list, String fileName) throws IOException {
		FileWriter fileWriter = new FileWriter(fileName);
		try {
			fileWriter.write(titleLine+"\n");
			for (int i=0; i<list.length; i++){
				boolean isEmpty = true;
				String line = new String();
				for (int j=0; j<list[0].length; j++) {
					if (list[i][j] != 0) isEmpty = false;
					line += list[i][j];
					if (!(j == list[0].length - 1))
						line += ',';
					else line += '\n';
				}
				if (isEmpty) break;
				fileWriter.write(line);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			fileWriter.close();
		}
	}
}
