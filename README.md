# soap
Experimenting with how to hash files

## git, briefly
create a new file
git add it
	- hashes the file contents
	- stores it in .git/objects/<ab>/<cde..xyz> (where <ab> is the first 2 letters of hash and <cde..xyz> is the rest of the hash)
	- stores it in the .git/index with "filename\thash"

git stores directories:
	- list of type\tname\thash\n
	- hashes its contents and adds it to index
	
when committing:
	- git hashes index and compares it to hash of head
	- if it is different:
		- it creates hashes the contents of index
		- saves the contents in the same fashion as files and directories in object store
		- clears the index
		
Add some utilities for branching, logging, etc...
