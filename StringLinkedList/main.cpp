#include <iostream>
#include <stdlib.h>
#include <string>
#include "StringLinkedList.h"
#include "Stack.h"

int main()
{
    LinkedList l1;
    Stack ops;
    std::string filename;
    std::string command;
    std::string strg;
    std::cout << "Enter filename ('open filename.txt'): ";
    getline(std::cin, strg);
    command = strg.substr(0, strg.find(" "));
    if (command == "open") {
        filename = strg.substr(strg.find(" ") + 1);
        if (l1.openfile(filename)) {
            int pagenum = 1;

            std::cout << "\n------------Operations------------" << std::endl;
            std::cout << "1. Save file 'save filename.txt'" << std::endl;
            std::cout << "2. Insert text to nth line 'insert 5 this is a line'" << std::endl;
            std::cout << "3. Delete nth line 'delete 5'" << std::endl;
            std::cout << "4. Move nth line to mth line 'move 5 3'" << std::endl;
            std::cout << "5. Replace text at nth line 'replace 4 this is a line'" << std::endl;
            std::cout << "6. Display next page 'next'" << std::endl;
            std::cout << "7. Display prev page 'prev'" << std::endl;
            std::cout << "8. See operations 'ops'" << std::endl;
            std::cout << "9. Undo 'undo'" << std::endl;
            std::cout << "10. Enter 0 to exit" << std::endl;

            bool cnt = true;
            while (cnt) {
                std::cout << "Enter command: ";
                getline(std::cin, strg);
                command = strg.substr(0, strg.find(" "));
                strg = strg.substr(strg.find(" ") + 1);

                if (command == "0") {
                    exit(0);
                }
                else if (command == "save") {
                    strg = strg.substr(strg.find(" ") + 1);
                    l1.savefile(strg);
                    while (ops.size() != 0) {
                        ops.pop();
                    }
                }
                else if (command == "insert") {
                    std::string linenumber = strg.substr(0, strg.find(" "));
                    strg = strg.substr(strg.find(" ") + 1);
                    std::string deletedline = l1.insertline(stoi(linenumber), strg);
                    pagenum = ceil(stof(linenumber) / 10);
                    l1.displaypage(pagenum);
                    std::string newstring = command + " " + linenumber + " " + deletedline;
                    ops.push(newstring);
                }
                else if (command == "delete") {
                    std::string deletedline = l1.deleteline(stoi(strg));  //burada strg 5 stringine sayýsýna eþit
                    pagenum = floor(stof(strg) / 10) + 1;
                    if (pagenum % 10 == 0) {
                        pagenum--;
                        l1.displaypage(pagenum);
                    }
                    else l1.displaypage(pagenum);
                    std::string newstring = command + " " + strg + " " + deletedline;
                    ops.push(newstring);
                }
                else if (command == "move") {
                    std::string line1 = strg.substr(0, strg.find(" "));     // 3
                    std::string line2 = strg.substr(strg.find(" ") + 1);    // 5
                    l1.moveNtoM(stoi(line1), stoi(line2));
                    int a = floor(stof(line1) / 10) + 1;
                    int b = floor(stof(line2) / 10) + 1;
                    if (a == b) {
                        l1.displaypage(a);
                    }
                    else {
                        l1.displaypage(a);
                        l1.displaypage(b);
                    }
                    std::string newstring = command + " " + line2 + " " + line1;
                    ops.push(newstring);
                }
                else if (command == "replace") {
                    std::string linenum = strg.substr(0, strg.find(" "));
                    strg = strg.substr(strg.find(" ") + 1);
                    std::string replacedline = l1.replacetext(stoi(linenum), strg);
                    pagenum = floor(stof(linenum) / 10) + 1;
                    if (stoi(linenum) % 10 == 0) {
                        pagenum--;
                        l1.displaypage(pagenum);
                    }
                    else l1.displaypage(pagenum);
                    std::string newstring = command + " " + linenum + " " + replacedline;
                    ops.push(newstring);
                }
                else if (command == "next") {
                    pagenum++;
                    l1.displaypage(pagenum);
                }
                else if (command == "prev") {
                    pagenum--;
                    if (pagenum > 0) {
                        l1.displaypage(pagenum);
                    }
                    else {
                        pagenum = 1;
                        std::cout << "You are at first page.\n";
                        l1.displaypage(pagenum);
                    }
                }
                else if (command == "ops") {
                    ops.print();
                }
                else if (command == "undo") {
                    ops.undo(l1);
                }
            }
            return 0;
        }
    }
    else return 0;
}
