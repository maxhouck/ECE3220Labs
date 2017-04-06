/*
 * main.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: Max
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>

void error_message();
void display_menu();

class Signal{
	private:
		int length;
		double maximum;
		double average;
		double *signal;
		std::string filename;
		void read_file();
		void set_maximum();
		void set_average();
	public:
		Signal(); //take a default input file and reads signal and allocate memory accordingly
		Signal(int filenumber); //takes "Raw_data_nn.txt" read signal and allocate memory
		Signal(char* filename);//take filename and inputs and allocates
		~Signal(); //destructor
		void offset(double offset);
		void scale(double scale);
		void center();
		void normalize();
		void statistics();
		void Sig_info();
		void Save_file(char* savefilename);
};

Signal::Signal() {
	this->filename = "Raw_data_00.txt";
	read_file();
}

Signal::Signal(char* infilename) {
	this->filename = infilename;
	read_file();
}

Signal::Signal(int filenumber) {
	//parse file number argument
	filename = "Raw_data_00.txt";
	if(filenumber < 9) { //one digit file number
		filename.at(10)=filenumber;
	}
	else if (filenumber < 100) { //two digit file number
		filename.at(10) = filenumber % 10; //second digit
		filename.at(9) = filenumber / 10;  //first digit
	}
	else if (filenumber >= 100) { //more than two digits = error
		std::cout << "Error. File number too big";
		exit(1);
	}
	read_file();
}

void Signal::set_maximum() {
	int i;
	double maximum = *signal;
	for(i=0;i<length;i++) {
		if(*(signal+i) > maximum)
			maximum = *(signal+i);
	}
}

int main(int argc, char* argv[]) {
	//parse input
	char* filename;
	char* filenumber;
	char* argument;
	Signal signal;
	int i;
	if(argc==1)
		signal = Signal();
	else {
		for(i=1;i<argc;i++){
			argument = argv[i];
			if(*argument != '-') error_message();
			switch(*(argument+1)) {
				case 'n':  //file number
					argument = argv[++i];
					filenumber = argument;
					signal = Signal(atoi(filenumber));
					break;

				case 'f': //file name
					argument = argv[++i];
					filename = argument;
					signal = Signal(filename);
					break;

				default: error_message();
			}
		}
	}

	char choice;
	while(choice != 'e') {
		display_menu();
		std::cin.clear();
		std::cin >> choice;
		switch(choice) {
			case 'o':
				int offset;
				std::cout << "Enter offset: ";
				std::cin >> offset;
				signal.offset(offset);
				break;

			case 's':
				double scale;
				std::cout << std::endl;
				std::cout << "Enter scale: ";
				std::cin >> scale;
				signal.scale(scale);
				break;

			case 'c':
				signal.center();
				break;

			case 'n':
				signal.normalize();
				break;

			case 'i':
				signal.Sig_info();
				break;

			case 'a':
				std::cout << "Enter name of saved file: ";
				char* savename;
				std::cin >> savename;
				signal.Save_file(savename);
				break;

			case 'e':
				exit(1);
				break;

			default:
				std::cout << "Not a valid option" << std::endl;
		}
	}
	return 1;

}

void Signal::read_file() {
	FILE *readfile;
	readfile = fopen(filename.c_str(),"r"); //opening file
	if(readfile == NULL) { //error checking
		std::cout << "Error opening file.";
		exit(1);
	}

	fscanf(readfile,"%d %f",&length,&maximum);
	double* signal = (double*) malloc(sizeof(double)*length);
	for(int i = 0; i < length; i++) //scanning in data
 		fscanf(readfile,"%f",(signal+i));

	fclose(readfile); //close file

}

void Signal::set_average() {
	int i;
	double sum=0;
	for(i = 0; i < length; i++) {
		sum += *(signal+i);
	}
	average = sum / length;
}

void Signal::offset(double offset) {
	int i;
	for(i = 0; i < length; i++)
		*(signal+i) += offset;
}

void Signal::scale(double scale) {
	int i;
	for(i = 0; i < length; i++)
		*(signal+i) *= scale;
}

void Signal::center() {
	set_maximum();
	offset(-maximum/2);
}

void Signal::normalize() {
	set_maximum();
	set_average();
	scale(1/average);
}

void Signal::Sig_info() {
	set_maximum();
	set_average();
	std::cout << "Length: " << length << std::endl;
	std::cout << "Maximum: " << maximum << std::endl;
	std::cout << "Average: " << average << std::endl;
}

void Signal::Save_file(char* savefilename) {
	FILE *writefile; //same as rename_data
	writefile = fopen(savefilename,"w"); //open file
	if(writefile == NULL) {
		std::cout << "Error opening write file." << std::endl;
		exit(0);
	}
	fprintf(writefile,"%.0f %.4f\n", maximum, length); //write max and length
	for(int i = 0; i < length; i++) //write the rest of the data
		fprintf(writefile,"%.4f\n",*(signal+i));
	fclose(writefile);
}

Signal::~Signal() {
	//free(signal);
}
/*
void rename_data(float* data, char* rename) {
	FILE *writefile;
	writefile = fopen(rename,"w"); //open file
	if(writefile == NULL) {
		printf("Error opening write file.");
		exit(0);
	}
	fprintf(writefile,"%.0f %.0f\n", *(data), *(data+1)); //write max and length
	for(int i = 0; i < *(data); i++) //write the rest of the data
		fprintf(writefile,"%.4f\n",*(data+i+2));
	fclose(writefile);

}*/

/*void scale_data(float* data_in, float scale, char* filenumber) {
	int length = (int) *(data_in);
	float* data = malloc(sizeof(float)*(length+2));
	memcpy(data,data_in,sizeof(float)*(length+2));

	int i;
	for(i = 0; i < *(data); i++) //index of data is 1 higher
		*(data+i+2) *= scale;

	//parse file number argument
	char filename[] = "Scaled_data_00.txt";
	if(atoi(filenumber) < 9) { //one digit file number
		*(filename+13)=*filenumber;
	}
	else if (atoi(filenumber) < 100) { //two digit file number
		filename[13] = *(filenumber+1);
		filename[12] = *(filenumber);
	}

	FILE *writefile; //same as rename_data
	writefile = fopen(filename,"w"); //open file
	if(writefile == NULL) {
		printf("Error opening write file.");
		exit(0);
	}
	fprintf(writefile,"%.0f %.4f\n", *(data), scale); //write max and length
	for(int i = 0; i < *(data); i++) //write the rest of the data
		fprintf(writefile,"%.4f\n",*(data+i+2));
	fclose(writefile);

}*/

/*void statistics(float* data, char* filenumber) {
	float sum=0, max = *(data+2); //find maximum and average
	int length = (int)*(data);
	for(int i = 0; i < length; i++) {
		sum+=*(data+i+2);
		if(max < *(data+i+2))
			max = *(data+i+2);
	}
	float average = sum / length;

	//parse file number argument
	char filename[] = "Statistics_data_00.txt";
	if(atoi(filenumber) < 9) { //one digit file number
		*(filename+17)=*filenumber;
	}
	else if (atoi(filenumber) < 100) { //two digit file number
		filename[17] = *(filenumber+1);
		filename[16] = *(filenumber);
	}

	FILE *writefile; //same as rename_data
	writefile = fopen(filename,"w"); //open file
	if(writefile == NULL) {
		printf("Error opening write file.");
		exit(0);
	}
	fprintf(writefile,"%.4f %.0f\n", average, max); //write max and average
	fclose(writefile);

}
*/
/*void Signal::center() {
	int length = (int) *(data_in); //used same offset code as above
	float* data = malloc(sizeof(float)*(length+2));
	memcpy(data,data_in,sizeof(float)*(length+2));

	int i;
	float sum=0, max = *(data+2); //find max and average
	for(int i = 0; i < length; i++) {
		sum+=*(data+i+2);
		if(max < *(data+i+2))
			max = *(data+i+2);
	}
	float average = sum / length;

	for(i = 0; i < length; i++) //center / offset the data
		*(data+i+2) -= average;

	//parse file number argument
	char filename[] = "Centered_data_00.txt";
	if(atoi(filenumber) < 9) { //one digit file number
		*(filename+15)=*filenumber;
	}
	else if (atoi(filenumber) < 100) { //two digit file number
		filename[15] = *(filenumber+1);
		filename[14] = *(filenumber);
	}

	FILE *writefile; //same as rename_data
	writefile = fopen(filename,"w"); //open file
	if(writefile == NULL) {
		printf("Error opening write file.");
		exit(0);
	}
	fprintf(writefile,"%.0f %.4f\n", *(data), average * -1); //write max and length
	for(int i = 0; i < *(data); i++) //write the rest of the data
		fprintf(writefile,"%.4f\n",*(data+i+2));
	fclose(writefile);

}
*/
/*
void normalize(float* data_in, char* filenumber) {
	int length = (int) *(data_in); //used same offset code as above
	float* data = malloc(sizeof(float)*(length+2));
	memcpy(data,data_in,sizeof(float)*(length+2));

	int i;
	float max = *(data+2); //find max and average
	for(int i = 0; i < length; i++)
		if(max < *(data+i+2))
			max = *(data+i+2);


	for(i = 0; i < length; i++) //normalize the data
		*(data+i+2) /= max;

	//parse file number argument
	char filename[] = "Normalized_data_00.txt";
	if(atoi(filenumber) < 9) { //one digit file number
		*(filename+17)=*filenumber;
	}
	else if (atoi(filenumber) < 100) { //two digit file number
		filename[17] = *(filenumber+1);
		filename[16] = *(filenumber);
	}

	FILE *writefile; //same as rename_data
	writefile = fopen(filename,"w"); //open file
	if(writefile == NULL) {
		printf("Error opening write file.");
		exit(0);
	}
	fprintf(writefile,"%.0f %.4f\n", *(data), 1/max); //write max and length
	for(int i = 0; i < *(data); i++) //write the rest of the data
		fprintf(writefile,"%.4f\n",*(data+i+2));
	fclose(writefile);

}
*/

void error_message() {
	std::cout << "ERROR. Usage: \n \t-n <file number> \n\t-f <file name>" << std::endl;
	exit(0);
}

void display_menu() {
	std::cout << "Menu:" << std::endl;
	std::cout << "\t(o)ffset" <<std::endl;
	std::cout << "\t(s)cale" << std::endl;
	std::cout << "\t(c)enter" << std::endl;
	std::cout << "\t(n)ormalize" << std::endl;
	std::cout << "\tshow (i)nfo" << std::endl;
	std::cout << "\ts(a)ve" <<std::endl;
	std::cout << "\t(e)xit" << std::endl;
	std::cout << "Make a selection:" << std::endl;
}
