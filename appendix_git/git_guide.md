# Git:

## What is Git?

Git is a version control tool, what does this mean?

It means that you no longer need to go from **project.cpp**, to **project_final.cpp**, and even to **project_final_real.cpp**. As Git will save only the changes you made to the files and will help you to collaborate with others in a clean way.

It was created by Linus Torvalds, yes the creator of Linux, who also had problems with versioning of his own codes.

It can work in your machine with terminal tools or [VS Code](https://code.visualstudio.com/). But if you need to collaborate, you may need to consider [Github](https://github.com/) and [Gitlab](https://about.gitlab.com/)

### Why is it important?

There are many reasons, some of them are:

- It is an efficient way to manage your projects and codes.
- It is a proffesional tool for proffesional development and growth.
- It will help you to collaborate in teams.
- It allows you to publish your projects.

## First steps with Git

Most of the Linux systems comes with Git installed.

So, let's begin wit checking it:

~~~bash
git --version
# Should display the installed version, otherwise check the installation.
~~~

Then, create a directory to explore things:

~~~bash
mkdir my_project
cd my_project
~~~

Now, we are ready to start the Git in this folder, run the next command:

~~~bash
# git init [params]
git init
~~~

You should see a display of the config made, it may be asking you to set the default branch if it is your first time. In the past, the main branch was called **master**. However, it has changed to **main** or **trunk**. To achieve this change you can run:

~~~bash
# git config 
git config --global init.defualtBranch main
~~~

Inside your project, let's proceed with this change by running:

~~~bash
# git branch [params] <branch>
#   -m To change  from old branch to new branch
git branch -m main
~~~

We have set up the branch, but there are still configurations you have to implement:

~~~bash
# User name set up
git config --global user.name "<your_username>"
# User email set up
git config --global user.email "<your_email>"
~~~

If you desire so, you can check all the configurations with:

~~~bash
git config --list
~~~

## Basic commands:

Once you have initialized *Git* you are ready to control the versions of your code.

~~~bash
# Remember, always initialize to work with Git
git init
~~~

But... what does the initialization do? Well, it add a **.git** directory to track the changes and will reflect all the git actions we implement. Do you see it? Well... it is a hidden dir. 

~~~bash
# Inside a git project, run:
ls -al
# Then search for the .git directory
~~~

So... let's being creating content

~~~bash
# Inside your git project
echo "New file with changes" > ./contenido.txt
~~~

Once you have done changes, you may be interested in know the status of changes, in this case you can try with the next command:

~~~bash
git status
~~~

![git_status_1_tm](/appendix_git/resources/git_status_1_tm.png)

Here, you can notice the following:

- You are on the branch master
- There are no commits
- The file you just added appears in untracked files

Now, to start tracking the file, you have to add it to git as shown below:

~~~bash
# git add [files_name] <file_name>
git add contenido.txt
~~~

Then, if you check the status it should be different.

![git_status_2_tm](/appendix_git/resources/git_status_2_tm.png)

In case you added a file you didn't want, you can revert it with:

~~~bash
# git rm --cached <filename>
git rm --cached cotenido.txt
~~~

But this is not the case, so make sure to add it again:

~~~bash
git add contenido.txt
~~~

If there are many files, and you want to import everything. You can simply run:

~~~bash
git add .
~~~

However, be careful when doing this, as you may accidentaly add undesired files if you do not check properly.

Now... Adding a file doesn't mean that the changes have been commited, it just add it to a staging phase to confirm and check, before committing a change. Then, the question becomes... how do I commit something in the stage file, easy:

~~~bash
# git commit -m "<message>"
git commit -m "My first change"
~~~

[TODO: Add commit image]

Is it still messy to understand the workflow of the changes? Let's illustrate it with next image:

![git_workflow_diagram](/appendix_git/resources/git_workflow_diagram.drawio.png)

# Additional resources:

- [Git Cheat Sheet | Github Education ](https://education.github.com/git-cheat-sheet-education.pdf)