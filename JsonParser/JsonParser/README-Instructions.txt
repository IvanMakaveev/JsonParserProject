Short instructions and project description:

This is an implementation of a JSON Parsing console app.
As such, it provides a console interface with a couple of callable functions.
All function calls must be on a single line! Any quotation marks ( " ) MUST be also included! 

Functions list and description:
* load "filePath.json"
- this function loads a JSON file. During it's loading, it validates the contents
and provides the user with feedback when/if errors occur and tells exactly which
line of text caused the error
- the function MUST be called before any other commands are invoked!

* print
- displays the contents of the currently loaded file on the screen in their current
state (including any changes made by the user during the lifespan of the app)

* search "keword"
- displays a list of all the nodes, whose object key is the same as the given keyword

* set "path" "json-formatted data"
- changes the data of the json object at the given path to the parsed json-formatted data
- the data must be formatted correctly, otherwise the parser will display an error similar 
to the load function
- the path can be pointing towards the root element, simply input: ""

* create "path" "json-formatted data"
- creates a new node based on the passed json-formatted data at the given path
- the data must be formatted correctly, otherwise the parser will display an error similar 
to the load function
- the path can be pointing towards the root element by adding only the name of the new member: "newMember"

* delete "path"
- deletes the node at the given path
- the root element cannot be deleted as it would make the file empty and therefore invalid

* move "from-path" "to-path"
- moves the memebers of the node at from-path to the node at to-path
- the from-path cannot be the root element!

* save ["path"]
- saves the node at the given path to the last file that was opened
- in order to save the root element, just the second path

* saveas "filePath.json" ["path"]
- saves the node at the given path to the given file path
- in order to save the root element, just skip the second path

* exit
- closes the program

Any error will be displayed on the console. Any memory leaks have been caught inside of try-catch blocks 
in the dedicated creation functions:
- The ApplicationExecutor deletes the command if it throws after running
- The Parser deletes the created nodes if one of them throws during creation
- Each node deletes and manages all of its children
- The JsonDataModel handles its root node deletion in the destructor
- All files are closed as soon as possible and are opened only once per command (once for reading and once for writing)

All the validation of the JSON data is automatically done by the parser. It uses token-based recursive creation of the
nodes. If an error occurs, all created nodes are deleted and the program displays on which line the error was.

I have provided a file called "sample.json"
You can apply the following list of commands to test the functionallity:

load "sample.json"
print
    // should display the contents of the json file
search "name"
    // should display the names of the company, groups and the employees
set "average salary" "1400"
set "list of workgroups/0/name" ""Group CEO""
    // should change the name of the first group to "Group CEO" and set the average salary to 1400
set "error field" "{ "error message" : null}"
    // should change the error field data
create "company location" ""Bulgaria""
    // should add a member to the root element called "company location" with value "Bulgaria"
print
    // should display the changed json data
delete "error field"
    // should delete the error field
move "list of workgroups/1/members" "list of workgroups/0/members"
    // should move the members from the second group to the first group
saveas "result.json"
    // should save the changes as "result.json"
exit