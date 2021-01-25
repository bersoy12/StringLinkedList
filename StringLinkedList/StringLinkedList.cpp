#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "StringLinkedList.h"
#include "Stack.h"

void LinkedList::addtotail(std::string strg) {
    if (listempty()) {      // liste boþ ise
        tail = new Node;
        tail->str = strg;
        tail->next = NULL;
        head = tail;
    }
    else {                  //liste boþ deðilse
        Node* temp = new Node;
        temp->str = strg;
        tail->next = temp;
        tail = temp;
    }
    size++;
}

bool LinkedList::listempty() {
    if (size==0) return 1;
    else return 0;
}

bool LinkedList::openfile(std::string strg) {
    std::ifstream in_file;
    in_file.open(strg);
    if (!in_file) {
        std::cerr << "Problem opening file" << std::endl;
        return 0;
    }
    else {
        std::string line{};
        while (std::getline(in_file, line)) {
            addtotail(line);
        }
        std::cout << "File was loaded." << std::endl;
        in_file.close();
        return 1;
    }
}

bool LinkedList::savefile(std::string filename) {
    std::ofstream out_file(filename, std::ios::trunc);
    if (!out_file) {
        std::cerr << "Error writing file" << std::endl;
        return 1;
    }
    else {
        std::string line;
        Node* temp = head;
        while (temp->next != NULL) {
            line = temp->str;
            out_file << line;                   //saves first line
            temp = temp->next;
            if (temp->next == NULL) {
                line = temp->str;       
                out_file << std::endl;          // gets into new line 
                out_file << line;               // writes to this line
                break;
            }
        }
        std::cout << "File saved." << std::endl;
    }

    out_file.close();
}

void LinkedList::displaypage(int page) {
    float sizef = size;
    if (page <= ceil(sizef / 10)) {                 // if user inputted page number exceeds the existing pages: input 1, total pages 2
        if (!listempty()) {
            int n = (page - 1) * 10 + 1;
            int m = n + 10;
            Node* temp = head;
            for (int i = 1; i < n; i++) {           // if input is 2, temp pointer moves to 2nd page's begining which is 11th line
                temp = temp->next;
            }
            for (int j = 1; j < 11; j++) {          // this outputs 10 lines
                if (temp->next == NULL) {
                    std::cout << n++ << ") ";       // this outputs 9 lines
                    std::cout << temp->str << std::endl;
                    break;
                }
                std::cout << n++ << ") " << temp->str << std::endl;     //this outputs last line in that page
                temp = temp->next;
            }
            std::cout << std::endl;
            std::cout << "----------- Page " << page << " -----------" << std::endl;
            std::cout << std::endl;
        }
        else {                                      // if list is empty, there is not any page to display.
            std::cout << "List is empty.\n";
        }
    }
    else {
        std::cout << "Page number is " << page << std::endl;
        std::cout << "No lines here.\n" << std::endl;
    }
}

std::string LinkedList::insertline(int n, std::string strg) {  //insert 5 hello my friend
    std::string linestr;        //no need to push stack bcs it is going to be deleted only in undo function
    if (listempty()) {
        addtotail(strg);
        return "";              
    }
    else if (size < n) {                //if inserted line exceeds the size, we should put empty line till inserted line
        while (size < n-1) {
            addtotail(" ");
        }
        addtotail(strg);
        return "";
    }
    else {                      //condition n<=size
                                // in case we insert the new line between existing lines
                                //if size is 10 and we insert 10th line,
        if (n == 1) {           //if there is only one element in the list
            addtohead(strg);
            return "";
        }
        Node* prev = head;
        Node* cur = prev->next;
        for (int count = 1; count != n - 1; count++) {
            prev = prev->next;
            cur = cur->next;
        }
        if (cur->str == " ") {
            linestr = " ";
            cur->str = strg;
        }
        else {
            Node* temp = new Node;
            linestr = temp->str;
            temp->str = strg;
            temp->next = cur;
            prev->next = temp;
        }
        size++;
        return linestr;
    }
}

std::string LinkedList::deleteline(int n) {
    std::string deletedline;
    if (!listempty()) {  // list is not empty
        if (size == 1) {     //delete only node of list with 1 element
            deletedline = head->str;
            head = tail = NULL;
        }
        else if (n == size) {      //deleting last node
            Node* cur = head;
            while (cur != tail) {
                if (cur->next == tail) {
                    deletedline = tail->str;
                    tail = cur;
                    tail->next = NULL;
                    return deletedline;
                    break;
                }
                cur = cur->next;
            }
        }
        else if (n == 1) {
            Node* temp = head;
            head = head->next;
            deletedline = temp->str;
            temp->next = NULL;
        }
        else {
            Node* cur = head->next;
            Node* prev = head;
            for (int i = 1; i < n - 1; i++) {
                cur = cur->next;
                prev = prev->next;
            }
            deletedline = cur->str;
            prev->next = cur->next;
            cur->next = NULL;
        }
        size--;
        return deletedline;
    }
    else return "List is empty.";
}

void LinkedList::moveNtoM(int n, int m) {
    if (n < size + 1 && m < size + 1) {
        Node* ptrM = head;
        Node* ptrN = head;
        for (int i = 1; i < m; i++) {
            ptrM = ptrM->next;
        }
        for (int j = 1; j < n; j++) {
            ptrN = ptrN->next;
        }
        std::string tempstr;
        tempstr = ptrM->str;
        ptrM->str = ptrN->str;
        ptrN->str = tempstr;

        std::cout << "These lines are switched: " << n << " and " << m << std::endl;
    }
    else std::cout << "One of the integers exceeds the size.\n";
}

std::string LinkedList::replacetext(int n, std::string strg) { //replace text inside line n
    std::string replacedline;
    if (!listempty() && n<size) {
        Node* temp = head;
        for (int i = 1; i < n; i++) {
            temp = temp->next;
        }
        replacedline = temp->str;
        temp->str = strg;
        return replacedline;
    }
    else if (n == size) {
        replacedline = tail->str;
        tail->str = strg;
        return replacedline;
    }
    else if (n > size) {
        insertline(n,strg);
        return "";
    }
    else return "";
}

std::string LinkedList::firstnode() {
    return head->str;
}

void LinkedList::addtohead(std::string strg) {
    if (listempty()) {
        Node* temp = new Node;
        temp->str = strg;
        temp->next = NULL;
        head = temp;
    }
    else {
        Node* temp = new Node;
        temp->str = strg;
        temp->next = head;
        head = temp;
    }
    size++;
}

std::string LinkedList::deletefromhead() {
    std::string strg = head->str;
    Node* temp = head;
    if (size == 1) {
        head = tail = NULL;
        return strg;
    }
    else head = head->next;
    return strg;
}

void LinkedList::displayall() {
    for (Node* temp = head; temp != NULL; temp = temp->next) {
        std::cout << temp->str << std::endl;
    }
    std::cout << std::endl;
}
/*
void LinkedList::undo(Stack stk) {
    if (!stk.stackempty()) {
        std::string strg = stk.top();                           //insert 5 sadfsaf safdasfd asdfsd
        std::string lastop = strg.substr(0, strg.find(" "));    //lastop=insert
        strg = strg.substr(strg.find(" ") + 1);                 //5 asdfsdaf asdfsadf sdaffd
        if (lastop == "insert") {
            std::string linenum = strg.substr(0, strg.find(" "));       //5'i aldý
            deleteline(stoi(linenum));
            stk.pop();
        }
        else if (lastop == "delete") {                            //delete
            std::string linenum = strg.substr(0, strg.find(" "));       //4
            strg = strg.substr(strg.find(" ") + 1);                     //bir satýr
            insertline(stoi(linenum), strg);
            stk.pop();
        }
        else if (lastop == "move") {                              //move
            std::string line1 = strg.substr(0, strg.find(" "));     //3 
            std::string line2 = strg.substr(strg.find(" ") + 1);    //5
            moveNtoM(5, 3);
            stk.pop();
        }
        else if (lastop == "replace") {                         // replace 4 this is a line
            std::string linenum = strg.substr(0, strg.find(" "));     //4
            strg = strg.substr(strg.find(" ") + 1);                 //line
            replacetext(stoi(linenum), strg);
            stk.pop();
        }
        else {
            "Operation stack is empty.";
        }
    }
    else {
        std::cout << "No operations have been done yet.\n" << std::endl;
    }
}
*/