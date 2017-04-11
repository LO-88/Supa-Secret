# How to use GitHub

Once you have GitHub installed, it can be used for version controlling as well as easy collaboration. The general process for using GitHub involves forking, commiting, and then submiting a pull request. This document outlines the necessary steps.

The url for this repository is: https://github.com/dascheltfortner/Supa-Secret.git

# Introduction to Git

The main idea behind Git is version controlling between groups for easy sharing of code. For this project, all the code for the project will be held in this repository. What GitHub allows us to do is download the code off of the internet onto our local machines so that we can edit it in Visual Studio. In addition to this, we can push the code back onto this repository once we've made our changes, and GitHub will update this repository and keep track of the changes. This makes it so if we are both working on the code and suddenly it breaks, we can easily go back to an old version, or know what broke it. We can also both edit the code without needing to be at the same machine.

# Instructions for Using Git/GitHub

Enough blabbering. Let's go.

#### 1.  Become a Collaborator

You should have gotten an email notifying you that you have been invited to collaborate on GitHub. You want to accept this invitation. This will allow you to edit and modify the contents of this repository.

#### 2.  Fork the Repository

Open up your favorite browser and navigate to https://github.com/dascheltfortner/Supa-Secret.git. This is the repository for our project. (Of course you already got here because you're reading this) Click on the button that says `Fork` at the top right corner of the page. This will create a copy of the repository into your GitHub account. This way we can make changes to the code without modifying the code that already exists, so that we don't mess something up big time and then lose a bunch of stuff.

#### 3.  Set Up Your User Configurations

Now that you have copied this repository to your account, you need to fire up Windows Powershell. You could also use Git Bash if you wanted to, but I prefer Powershell. You will probably have to set up your user name and email and stuff in the command line. So, in Windows Powershell type 

> `git config --global user.name "YOUR NAME"`

This will configure your username. To configure your user name use the command

> `git config --global user.email "EMAIL ADDRESSS"`

This configures your email. I don't think this is necessary.

#### 4. Fire Up Ye Olde Visual Studio

Create the project that you want to use for Homework 6. Name it whatever you want, and put it wherever you want. Once you have a new project, go to Powershell and cd to to that location. The command is the same as the Linux environment on John, so you just need to navigate to the folder that contains the source code for your Visual Studio project. Once you're there, type this in the console:

> `git init`

This initializes the folder for a git repository. 