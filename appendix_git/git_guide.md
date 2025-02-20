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

![git_commit](/appendix_git/resources/git_commit.png)

With this, you just committed a change. The committed changes can be tracked and you can check the history of your project.

How to check the history of changes? You can check the logs in git for your repository with:

~~~bash
git log
~~~

![git_log](/appendix_git/resources/git_log.png)

Not so much changes for now, so try adding multiple commits and check it later. Keep in mind that if you modify a file that was already in the history of a repository, you won't add a untracked file but rather to add a modified tracked file.

Is it still messy to understand the workflow of the changes? Let's illustrate it with next image:

![git_workflow_diagram](/appendix_git/resources/git_workflow_diagram.drawio.png)

## Branches and merges:

A branch is a division of your workspace in multiple space, so you can focus in different things. For example, you may have the **main** branch, where your base application is present, and the **dev** branch, where you experiment and add features. Later, when all was setup in the **dev** branch, you can merge its content to the **main** branch.

This also allows a better collaboration and the implementation of features, bug fix and changes in a better and tracked way.

Don't you know which branch are you on? Just run the next command:

~~~bash
git branch
~~~

At this point, you should only have one branch, it can be **master** or **main** depending on your set up. 

To create one branch, you can use:

~~~bash
# git checkout -b <branch_name>
git checkout -b dev

# After that, check the creation
git log
~~~
![git checkout -b branch](/appendix_git/resources/git_branch.png)

You can add and commit changes that are independent of other branches, for example, you can run:

~~~bash
echo "Commit in another branch" >> ./contenido.txt
git add contenido.txt
git commit -m "Changes in other branch"
~~~

If you change branches, you wouldn't notice the changes. But... how can you add the changes to the main branch when I think I am ready? Well, you just need to merge it:

~~~bash
# Move to your main branch
git checkout master # Or git switch master

# Merge and specify the branch
git merge dev
~~~

It will notify you about the changes and notifications, after this you would be able to watch the changes, so check with the logs.

~~~bash
git log
~~~

![git_log_2](/appendix_git/git_guide.md)

Finally, do not forget about deleting branches once their purpose was completed, you can run:

~~~bash
# git branch -D <branch>
git branch -D dev
~~~

## Time travel:

Did you ever wondered how to travel to the past and correct a mistake? Well, it is impossible to know. However, we can go back with **Git** to previous versions of our code to make changes, there are two options **reset** and **revert**:

- ```git reset``` : Return to a previous commit, deleting the history of changes until that point. It also allows to explore past changes.
- ```git revert``` : Return to a previous commit by creating a new commit in that point.

Keep in mind to check for the **HEAD** that is where you created the last commit, for example, it can be *main* if you just merged two branches (*dev* merged to *main*)

Let's take a look in a more practical way, we have a history of 3 commits:

![git_log-3](/appendix_git/resources/git_log_3.png)

But, we added a change we didn't really want. So I have to come back now, I can achieve it by using a *revert* with a proper commit in mind, so we will take a look on the commit ID/hash.

~~~bash
# git revert <id/hash_of_commit>
# In my case, it would be:
git revert 096f8c5a9ec524026d545ab24b4debfb55aa309d
~~~

And it will display you the notification (in a text editor) to specify the commit of revert, like this:

![git_revert_act](/appendix_git/resources/git_revert_act.png)

Now, if you check the logs, you may notice important additional information:

~~~bash
git log
~~~

![git_log_4](/appendix_git/resources/git_log_4.png)

In case you have a conflict with the *revert*, you have three options:

- Fix the conflicts and continue:

~~~bash
# After making the fix
git revert --continue
~~~

- Skip the patch:

~~~bash
git revert --skip
~~~

- Cancel the rever operation

~~~bash
git revert --abort
~~~

Then, why don't we try to reset the history of our repository? Of course, we will do it with the commit that was reverted:

~~~bash
# git reset <option> <commit>
#       --soft: HEAD to the specified commit, preserves the changes in staging area
#       -- mixed: Default, moves HEAD, discard changes in staging area but mantains changes in working dir.
#       -- --hard: Moves HEAD but discard all the changes
git reset --hard 096f8c5a9ec524026d545ab24b4debfb55aa309d
~~~

![git_log_5](/appendix_git/resources/git_log_5.png)

Always ensure to use **--hard** as last option, as you are affecting the history of changes and the workflow of others.

Take advantage of this tools only to improve your work, fix bugs and by considering a proper communication with the team.

## Managing versions:

You can have different versions by considering **tags** or **checks**.

On one hand, **tags** it like a stamp you add to a commit for a easy future identification, for example, by identifying a commit with a key work version like Ubuntu does with its distros (Utopic Unicorn, Wily Werewolf, Focal Fosa, Jammy Jellyfish...) or just to manage alfa, betas and stable versions.

~~~bash
# Adding a tag
# git tag [option] <name>
#       -a : To make an unsigned annotated tag object
#       -m : To submit a message
git tag -a v1.0 -m "First version"
~~~

Did you already give it a try? If the answer is no, check the images below to check the changes between **logs**.

![git_log_6](/appendix_git/resources/git_log_6.png)

As you can see, the last commit has the tag we just created, but... what happens when I have a lot of commits and a few tags? Do I really need to explore all the commits to find the tags? The answer is *no*, as you can list only the tags as follows:

~~~bash
# Lsit available tags
git tag
~~~

If you have the version we just created, it should only appear that. Try to add more commits and versions, and compare the listing.

Another interesting option here, is to show the specified version, this can be done as it illustrated below:

~~~bash
git show v1.0
~~~

![git_show_tag](/appendix_git/resources/git_show_tag.png)

Let's say you added a wrong tag, there is still the option to delete it with the command:

~~~bash
# git tag [option] <tag>
#       -d : Delete the given tag
git tag -d v1.0
~~~

By deleting a tag, you do not mess the commit story. You just delete a version tag, which can be replaced or taken to another position.

On the other hand, **checkouts** allow to change branches or commits, in other words, it allow you to come back to specific commit or check another branch.

How? Well... run a **git log**, then select a commit, copy its ID and run the next command:

~~~bash
# git checkout <commit>
# In my case it is:
git checkout 6cf8b65ed188d0ef3e60d83703292f8db37be3e0
~~~

Then, you should notice the "time travel" as it can warn you about the position of the *HEAD* and how to implement changes from the commit you are currently on:

![git_checkout_sp_com](/appendix_git/resources/git_checkout_sp_com.png)

The command you can watch on screen is **swtich** which can help you to create a new branch from this point or just undo the operation (by providing ´´´-´´´ option)


# Additional resources:

- [Git Cheat Sheet | Github Education ](https://education.github.com/git-cheat-sheet-education.pdf)