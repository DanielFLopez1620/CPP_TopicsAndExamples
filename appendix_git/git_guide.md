# What is Git?

Git is a version control tool, what does this mean?

It means that you no longer need to go from **project.cpp**, to **project_final.cpp**, and even to **project_final_real.cpp**. As Git will save only the changes you made to the files and will help you to collaborate with others in a clean way.

It was created by Linus Torvalds, yes the creator of Linux, who also had problems with versioning of his own codes.

It can work in your machine with terminal tools or [VS Code](https://code.visualstudio.com/). But if you need to collaborate, you may need to consider [Github](https://github.com/) and [Gitlab](https://about.gitlab.com/)

## Why is it important?

There are many reasons, some of them are:

- It is an efficient way to manage your projects and codes.
- It is a proffesional tool for proffesional development and growth.
- It will help you to collaborate in teams.
- It allows you to publish your projects.

# First steps with Git

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