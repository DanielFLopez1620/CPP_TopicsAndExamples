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

The command you can watch on screen is **swtich** which can help you to create a new branch from this point or just undo the operation (by providing ```-``` option)

Be careful with the modifications over the history of commits, as you may not notice the latest changes and if you push/merge to a recent point, it may generate a conflict.

You can return to the last point of your branch, by providing its name.

~~~bash
# git checkout <branch>
git checkout main # Or master depending your set up
~~~

## Solving conflicts:

When we are working in a individual and local way, everything tends to go easy. However, when you add more people to the equation, **conflicts** may appear.

 These conflicts are not fights or problems, they are bugs and mistakes that happen when you merge branches. Then, the fusion alters the changes that were made in other branch that was recently merged.

 If this happen to you, do not worry as you can fix it. First, let's simulate a conflict in our repository.

1. In your main branch, create a change, for example:

~~~bash
echo "Let's create a conflict" > conflict.txt
~~~

2. Add the file to your repository history:

~~~bash
git add conflict.txt
git commit -m "Adding a non-conflicting file"
~~~

3. Then, we create another branch, for example:

~~~bash
git checkout -b devel
~~~

4. Make changes to the file in the new branch:

~~~bash
echo "Changes in devel" >> conflict.txt
~~~

5. Then, add the changes to the branch history:

~~~bash
git add conflict.txt
git commit -m "Is this a conflicting change?"
~~~

6. Go again to your original branch, in this case, it can be *master* or *main*

~~~bash
git checkout master # or main
~~~

7. Add a new change to the file in the main, making sure you haven't merge the changes from the other branch:

~~~bash
echo "Still not conflict, right? >> conflict.txt
~~~

8. And add those changes to the history of the repository at the current branch:

~~~bash
git add conflict.txt
git commit -m "A change in main with no conflict (not sure)"
~~~

9. Now, the two branches have changed, if we merge, it will have a conflict:

~~~bash
git merge devel
~~~

![git_conflict_1](/appendix_git/resources/git_conflict_1.png)

Now... how can we solve it? Well, you just need to edit the conflicting files by deciding what to leave... it can be only what is in *master*/*main* or only what is in *devel* or both or neither, as you wish:

~~~bash
nano conflict.txt

# And edit the file, you should see a similar structure as below.
~~~

![git_conflict_2](/appendix_git/resources/git_conflict_2.png)

What does it mean? The arrows indicate the changes origin (which is the branch?) and the equals indicate the separation between the changes.

Once you have solved it, check the status:

~~~bash
git status
~~~

![git_conflict_3](/appendix_git/resources/git_conflict_3.png)

After this, you can add and commit the changes, and then attempt the merge, which should be completed without any problems. 

##  VS Code and Git?

Yes, you can use the control version integrated in [VS Code](https://code.visualstudio.com/) to take advantage in your daily developing task.

Do you remember how to open it? Well, you just run:

~~~bash
code . # Or the path to your workspace and repository
~~~

Once inside, and if you are using a *Git* repository, you can go to the icon shown in the red circle to access it:

![vs_code_control_version](/appendix_git/resources/vs_code_control_version.png)

Here you can find a lot of tools to do the same you have done in terminal in order to control the versions of your code.

Some of the info you should consider is highlighted in the image below:

![vs_code_some_tools](/appendix_git/resources/vs_code_some_tools.png)

So, let's dive into this options:

- **Git options:** There you can find the tools for using *pull*, *push*, *fetch*, *clone*, *checkout*, *tags*, *remote*, *commit* and the options you have discovered previously in these lessons, but in this case using a GUI (Graphical User Interface).
- **Source control and tracking:** If you modify a file, you would see it right here. It will also track the staged files, and will give you the option to give a commit, you can select in a graphical way which file to move to the next stage.
- **History and branches:** It will display the histroy of your repo, with branches and merges included, if you pass over a commit you will get additional details.
- **Current branch:** It will indicate your current branch, and if you give click, you can move to other branches (local or remote) and even create a new one.
- **Current status:** Will tell you shortly about the changes and the current status of the repository.

But let's take things in a interesting way... did you know that you can also fix conflicts? Yes... coming back to this topic, if it happens in VS Code, it should be something like:

![vs_code_confict](/appendix_git/resources/vs_code_conflict.png)

Where you can explore in a graphical way the files and decide what to leave before the changes are merged. Here you can edit manually, or select an option (keep current change, keep incoming change and keep both). And as you can see it is helpful with colors and additional messages.

![vs_code_conflict_solved](/appendix_git/resources/vs_code_conflict_solved.png)

# Github:

## Why Github?

In a productive environment we need to share our work with others. Then, [Github](https://github.com/) appears a solution to control the versions and deploy online your repositories, and the most important thing is that *Git* is its core.

It isn't the only solution though, there are others like [BitBucket](https://bitbucket.org/product/), [GitLab](https://about.gitlab.com/), among others. However, Github is the most famous, it was released in February 2008.

Github offers a platform that aims to build, scale and submit secure software, even with AI powered tools, and in the case of the Enterprise edition it also adds AI (as it is transforming the software development), collaboration, productivity, security and scalability. It also automates some activities helping you to focus on the development.

One additional plus is that you can collaborate in projects, even bigger ones like programming languages and kernels, connecting with proffesionals around the world.

So, do not forget to create your account: [Sign In](https://github.com/login)

## Getting started with Github:

After you have created your account, let's explore the platform.

In the landing page, you can find the info ilustrated in the image below:

![github_landingpage](/appendix_git/resources/github_landingpage.png)


Do not forget to update your profile, where you can configure your name, your photo, your bio, the URL to your website, the company you are working on and links to your social media.

But the settings do not stop there, as you should also consider the security of your accound, considering the next factors:

- Use a strong password.
- Activate the [mobile 2FA](https://docs.github.com/en/authentication/securing-your-account-with-two-factor-authentication-2fa/configuring-two-factor-authentication), do not use SMS as double factor.
- Enable hte usage of secure keys.

After this, you are ready to explore the workflow with Git and Github.

## Working with Github:

You use *Git* inside *Github*, it is very important. However, there more things to do here, as you can explore new online tools to manage the versions of your code.

Some notes to consider are:

- *git init* is replaced as you can create a repository by using the GUI and then clone it into your machine.

- When you are done, you better move your local updates to the internet, in this case with different branches and using push, pull request and code review.

- It is better to divide the code review by considering smaller tasks, as it can be one task one objective.

Well, then let's begin with how to create a repository. In your home page, click the option to create a new repository:

![githuh_new_repo](/appendix_git/resources/github_new_repo.png)

Once you clic the option, you are ready to edit the details:

![github_create_repo](/appendix_git/resources/github_create_repository.png)


The aspects to focus here are:

- **Name:** How will be the identificator of your repository?
- **Propietary:** Who is the author? Can be a person, a group or a company.
- **Type:** Public or private, accoridng your requirements.
- **ReadMe file:** Specifiy if you want to create a repository with a markdown file to tell others what is going on here.
- **Add .gitignore:** A tempalte of a file that will host the things to ignore in the repository, for example, in C you will ignore the compiled results as you only need the source.
- **Add license:** Choose a license properly according to your objectives.

After you have done, the result should be like this:

![github_new_repository](/appendix_git/resources/github_new_repository.png)

Some additional keypoints are:

- You can check your branches here, at the moment we only have one, called **main**. However, if we create more, we could be able to select it.

- This also applys for tags, which can be checked at the side of the branches and at the **Releases** section.

- In the **About** section, you can find information about the repository including a short description, links to the **activity**, **stars**, **watching** and **forks**.

- You have windows for **Code** (where you develop), **Issues** (to solve issues notified by you or users), **Pull Requests** (invitations of merge of you or users you have received), **Actions** (for Github actions), **Projects** (for more about the project and relateds), **Wiki** (the documentation and wiki of the repository), **Security** (info related to the security of the repository), **Insighs** (important statistics of the repo) and **Settings** (Set up and configuration of your repository). We will check them out later, for now... let's dive in working together by adding a collaborator.

If you have a colleague or a friend who wants to participate in the project, you can add him/her as a collaborator. For this, go to **Settings** of your repository and check the option **Collaborators**.

![add_collaborators](/appendix_git/resources/github_add_collaborators.png)

You may have to give your 2FA credentials in order to make this happen. Once you in this screen, you can press the button **Add people** and type the username of the person you want to add.

That person must have a Github account and also accept the invitation before he/she is able to watch, modify and edit the repository.

Once, you are ready to continue, remember that you can work with the repository locally, but first you must clone it, how? Go to the green button called **Code**, copy the link and clone it in your terminal with:

~~~bash
git clone <url>
~~~

In my case (do not try the same repo as I configured it privetaly), it would be like this:

![github_git_clone](/appendix_git/resources/github_git_clone.png)

# Additional resources:

- [Git Cheat Sheet | Github Education ](https://education.github.com/git-cheat-sheet-education.pdf)