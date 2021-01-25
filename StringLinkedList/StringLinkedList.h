#ifndef STRINGLINKEDLIST_H
#define STRINGLINKEDLIST_H

class Node {
public:
    std::string str;
    Node* next;
};

class LinkedList {
private:
    Node* head, * tail;
    int size;
public:
    LinkedList() {
        head = tail = NULL;
        size = 0;
    }

    bool listempty();
    bool openfile(std::string);                     //opens file.txt
    bool savefile(std::string);                     //saves file and empties operation stack

    void displaypage(int);
    void addtotail(std::string);                    
    void addtohead(std::string);
    std::string deletefromhead();                   //returns deleted node
    std::string insertline(int, std::string);       //returns old line being inserted on it
    std::string deleteline(int);                    //returns deleted line
    void moveNtoM(int, int);                        //switches lines
    std::string replacetext(int, std::string);      //returns old line being replaced

    std::string firstnode();                        //returns first's string
    void displayall();
};

#endif // !STRINGLINKEDLIST_H

