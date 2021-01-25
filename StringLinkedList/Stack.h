#include "StringLinkedList.h"
#include <iostream>
#include <string>

class Stack {
private:
	LinkedList list;
	int stacksize;
public:
	Stack() {
		stacksize = 0;
	}

	bool stackempty() {
		if (stacksize == 0) return 1;
		else return 0;
	}

	void push(std::string str) {
		list.addtohead(str);
		stacksize++;
	}

	std::string top() {                 
		return list.firstnode();
	}

	std::string pop() {
		stacksize--;
		return list.deletefromhead();
	}

	int size() {
		return stacksize;
	}

	void print() {
		std::cout << "Operations applied to file:" << std::endl;
		list.displayall();
	}

    void undo(LinkedList l1) {
        if (!stackempty()) {
            std::string strg = top();                                       //insert 5 sadfsaf safdasfd asdfsd
            std::string lastop = strg.substr(0, strg.find(" "));            //lastop=insert
            strg = strg.substr(strg.find(" ") + 1);                         //5 asdfsdaf asdfsadf sdaffd
            if (lastop == "insert") {
                std::string linenum = strg.substr(0, strg.find(" "));       //5'i aldý
                l1.deleteline(stoi(linenum));
                pop();
            }
            else if (lastop == "delete") {                                  //delete
                std::string linenum = strg.substr(0, strg.find(" "));       //4
                strg = strg.substr(strg.find(" ") + 1);                     //bir satýr
                l1.insertline(stoi(linenum), strg);
                pop();
            }
            else if (lastop == "move") {                                    //move
                std::string line1 = strg.substr(0, strg.find(" "));         //3 
                std::string line2 = strg.substr(strg.find(" ") + 1);        //5
                l1.moveNtoM(stoi(line1), stoi(line2));
                pop();
            }
            else if (lastop == "replace") {                                 // replace 4 this is a line
                std::string linenum = strg.substr(0, strg.find(" "));       //4
                strg = strg.substr(strg.find(" ") + 1);                     //line
                l1.replacetext(stoi(linenum), strg);
                pop();
            }
            else {
                "Operation stack is empty.";
            }
        }
        else {
            std::cout << "Operation stack is empty.\n" << std::endl;
        }
    }
};