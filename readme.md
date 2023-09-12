+ display a prompt each time the user need to enter a command
+ we handle /bin/ls commands no flags no arguments
+ handle the errors in case that file isnt found
+ handle the file char (ctrl+d) should exit


---> Repeat the command entry : a loop (neeed to ask the user for his command). handle exit command (later use exit cmd)
---> use child process


-first: take entry of the user 
        sanatize the entry ("      /bin/ls" -> {"?bin?ls", NULL})
        turn the entry into a null termanated array
        create the child process
        run the commmand
        loop go again -> setp1

step 1: take user input 

-getline funnction 

step 2: sanitize the input

-get a count of text block

example: /bin/ls -l ->2 block (important to create the array)

-store each text block in the array we will use later

step 3: create the child process

- youll need the fork function

step 4: run the command 

-need the xecv command (execv implementing the path handling)
