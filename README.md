# String Linked List Project


Task in this project is to write a command-based text editor. 

- This text editor will print the contents of a file to the screen, page by page. 
- Each page consist of 10 lines. 

Program keeps the contents of the file in certain data structures,
and supports certain commands described below.

## Data Structures
### Features 
- Lines -string objects- are kept in a **linked list** structure. 
- Each line is stored in a separate node.
- A **stack** utilized in order to keep track of all actions carried out so that undo actions can be done. 

## Commands

While program is running, it repeatedly prints the contents of the
current file, and asks the user what user would like do. Valid commands are:

1. **open filename:** Opens the file whose name is provided in
the field `filename` and loads each line into linked list.
```
open filename.txt
```

2. **save filename:** Writes the contents of the linked list to the
file whose name is provided in the `filename` field.
```
save filename.txt
```

3. **insert n text:** Inserts a new line in the text at the **n**th line,
which contains the string provided in the field `text` ( hello my friend ).
```
insert 5 hello my friend
```

4. **delete n:** Deletes the line at position **n**.
```
delete 4
```

5. **move n m:** Moves the line at position **n** to position **m**.
```
move 5 8
```

6. **replace n text:** Program replaces the text inside line **n** with the
string provided in `text`.
```
replace 3 text
```

7. **next:** Contents of the file should not change, but displays
the next page.
```
next
```

8. **prev:** Contents of the file should not change, but displays
the previous page.
```
prev
```

9. **undo:** Reverts the last taken action. User is able to call as many
undo commands. Careful! Undo command does not include previous save or undo actions.
```
undo
```
