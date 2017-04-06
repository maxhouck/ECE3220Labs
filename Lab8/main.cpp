/*
 * main.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Max
 */

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <cstddef>
using namespace std;


class message{
	public:
		string messageText;
		message(); //constructor blank
		message(string newMessage); //constructor parametric
		~message(); //destructor
		virtual void print();
		message* nextMessage;
};

message::message() {
	cout << "Enter your message: " << endl;
	getline(cin,messageText);
	nextMessage = NULL;
}

message::message(string newMessage) {
	messageText = newMessage;
	nextMessage = NULL;
}

message::~message() {
//	delete(&messageText);
}

void message::print() {
	cout << messageText << endl;
}

class morseLetter {
	private:
		string morsecharacters;
	public:
		morseLetter(char c);
		~morseLetter();
		void print();
};

morseLetter::morseLetter(char c) {
	switch(c) {
		case 'a': case 'A': morsecharacters = ".-"; break;
		case 'b': case 'B': morsecharacters = "-..."; break;
		case 'c': case 'C': morsecharacters = "-.-."; break;
		case 'd': case 'D': morsecharacters = "-.."; break;
		case 'e': case 'E': morsecharacters = "."; break;
		case 'f': case 'F': morsecharacters = "..-."; break;
		case 'g': case 'G': morsecharacters = "--."; break;
		case 'h': case 'H': morsecharacters = "...."; break;
		case 'i': case 'I': morsecharacters = ".."; break;
		case 'j': case 'J': morsecharacters = ".---"; break;
		case 'k': case 'K': morsecharacters = "-.-"; break;
		case 'l': case 'L': morsecharacters = ".-.."; break;
		case 'm': case 'M': morsecharacters = "--"; break;
		case 'n': case 'N': morsecharacters = "-."; break;
		case 'o': case 'O': morsecharacters = "---"; break;
		case 'p': case 'P': morsecharacters = ".--."; break;
		case 'q': case 'Q': morsecharacters = "--.-"; break;
		case 'r': case 'R': morsecharacters = ".-."; break;
		case 's': case 'S': morsecharacters = "..."; break;
		case 't': case 'T': morsecharacters = "-"; break;
		case 'u': case 'U': morsecharacters = "..-"; break;
		case 'v': case 'V': morsecharacters = "..-"; break;
		case 'w': case 'W': morsecharacters = ".--"; break;
		case 'x': case 'X': morsecharacters = "-..-"; break;
		case 'y': case 'Y': morsecharacters = "-.--"; break;
		case 'z': case 'Z': morsecharacters = "--.."; break;
		case ' ': morsecharacters = " "; break;
		default: morsecharacters = "!"; break;
	}
}

morseLetter::~morseLetter() {
	//delete(&morsecharacters);
}

void morseLetter::print() {
	cout<<morsecharacters;
}

class morseCodeMessage : public message {
	private:
		void translate();
		vector<morseLetter> letters;
	public:
		morseCodeMessage(); //blank constructor
		morseCodeMessage(string newMessage);
		~morseCodeMessage(); //destructor
		void print();
};

morseCodeMessage::morseCodeMessage() : message() {
	translate();
}

morseCodeMessage::morseCodeMessage(string newerMessage) : message(newerMessage) {
	translate();
}

morseCodeMessage::~morseCodeMessage() {
	//delete(&letters);
}

void morseCodeMessage::translate() {
		int i;
		for(i=0;i<messageText.size();i++) {
			letters.push_back(morseLetter(messageText[i]));
		}
}

void morseCodeMessage::print() {
	message::print();
	int i;
	for(i=0;i<letters.size();i++) {
		letters[i].print();
		cout<<"   ";
	}
	cout<<endl;
}


class messageStack{
	private:
		message *firstMessage, *currentMessage;
	public:
		messageStack(message newMessage);
		~messageStack();
		void push(message newMessage);
		message* pop();
		void print_stack();
};

messageStack::messageStack(message newMessage) {
	firstMessage = &newMessage;
	currentMessage = firstMessage;
}

void messageStack::push(message newMessage) {
	currentMessage = firstMessage;
	while(currentMessage->nextMessage != NULL)
		currentMessage = currentMessage->nextMessage;
	currentMessage->nextMessage = &newMessage;
	currentMessage = currentMessage->nextMessage;
}

void messageStack::print_stack() {
	currentMessage = firstMessage;
	while(currentMessage != NULL) {
		currentMessage->print();
		currentMessage = currentMessage->nextMessage;
	}
}
messageStack::~messageStack() {

}

message* messageStack::pop() {
	if(firstMessage == NULL) { //make sure there is a first message
			cout << "Error. List is empty" << endl;
			exit(1);
		}
	if(firstMessage->nextMessage == NULL) { //special case for only 1 message
			currentMessage=firstMessage;
			firstMessage=NULL;
			return currentMessage;
		}
	currentMessage = firstMessage; //traverse to end of list
	while(currentMessage->nextMessage->nextMessage != NULL)
		currentMessage = currentMessage->nextMessage;
	//once were at end of list
	message *tempMessage;
	tempMessage = currentMessage->nextMessage->nextMessage;
	currentMessage->nextMessage = NULL;
	return tempMessage;
}

int main() {
	message m1 = message();
	message m2 = message("second message");
	message m3 = morseCodeMessage();
	morseCodeMessage m4 = morseCodeMessage("fourth message");
	m1.print();
	m2.print();
	m3.print();
	m4.print();
	messageStack messages = messageStack(m1);
	messages.push(m1);
	messages.push(m2);
	messages.push(m3);
	messages.push(m4);
	messages.push(m1);
	messages.push(m2);
	messages.push(m3);
	messages.push(m4);
	messages.pop();
	messages.print_stack();
}
