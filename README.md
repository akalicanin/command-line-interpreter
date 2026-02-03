# Command Line Interpreter

This is a command line interpreter. It is an object oriented project written in C++ in 2024-2025.
The project contains three example text files you can use, more about them in the Examples section.

## Features
- I/O redirection
- Pipelines
- Batch commands
- Syntax checking
- Error handling

## Commands
- echo  
  - ```echo <filename/text>```  
  - Prints to console.  
- head  
  - ```head -nX <filename/text>```  
  - Prints the first X amount of lines from the text. (example: head -n5)  
- prompt  
  - ```prompt <text>```  
  - Changes the prompt in the terminal. (the '>' symbol)  
- rm  
  - ```rm <filename>```  
  - Removes file.  
- time  
  - ```time```  
  - Prints current time  
- date  
  - ```date```  
  - Prints current date  
- touch  
  - ```touch <filename>```  
  - Creates a file. Error if it already exists.  
- tr  
  - ```tr <filename/text> <what> <with>```  
  - Replaces [what] with [with].  
  - [with] is optional, and if it isnt specified, it just removes all instances of [what].  
- truncate  
  - ```truncate <filename>```  
  - Empties file contents.  
- wc  
  - ```wc -c / wc -w <filename/text>```  
  - Word count, counting characters -c or words -w.  

## I/O redirection, pipelines, batch
### I/O redirection
I/O redirection works like this:  

    
``` echo "Hello World" >output.txt ```   
This will create a new file and put "Hello World" in it.

    
``` echo "Hello World" >>output.txt ```  
This will either create a new file, or append the text into an existing file.  

    
``` echo <input.txt ```  
This will read from an input file.  

    
You can combine input and output redirection in the same command.  
``` echo <input.txt >>output.txt ```  
  
It doesn't matter which one you put first, and whether or not there are blank spaces between the file name and < or > symbols.  
  
### Pipelines
Pipelines work using this character to seperate commands: '|'  
  
Pipelines can not work with output redirection, as the output is automatically redirected to the next command. 
  
Example of a pipeline:  
  
``` echo < commands.txt | head -n3 | tr "time" "date" | batch ```  
  
This will read the commands.txt file and pass it as output to the 'head' command, which will shorten it by 3 lines,   then replace "time" with date" and execute the text as a batch file.  

### Batch file
To create a batch file, use any regular text file and write seperate commands in each line.  
You have an example batch file provided: commands.txt  

## Examples

The repository comes with three files:  
- input.txt
- commands.txt
- files/input.txt

input.txt and files/input.txt are regular text files you can test using the echo command.

```
echo input.txt
echo files/input.txt
```

commands.txt is a batch file that creates a file called test.txt in your project folder, writes something into it, and then ends with an intentional error: non-existing command.  

```
batch commands.txt
```



