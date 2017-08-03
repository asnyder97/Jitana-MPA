# Jitana-MPA  (Malicious Path Analyzer)
### **Summer Research Project at University of Lincoln-Nebraska to expand functionality of [Jitana](https://github.com/ytsutano/jitana/tree/master). Mentored and collobrated wih [Mohannad Alhanahnah](https://github.com/Mohannadcse).  Faculty sponser [Prof. Qiben Yan](http://cse.unl.edu/~qyan/)**

#### Setup

Initally ran and tested on [Orcale VirtualBox](https://www.virtualbox.org/) running Ubuntu 16.04 LTS.

IDE:  [Eclipse Neon](http://www.eclipse.org/neon/)

Language: C++

#### Implementation

**Step One**

Download [Jitana](https://github.com/ytsutano/jitana/tree/master)
  Instructions in Jitana Readme file.
  
**Step Two**

Create cc mysql database and use [schema](https://github.com/asnyder97/Jitana-MPA/blob/master/db/schema) to create necassary tables.
  Special note:  this schema and use of IC3 is thanks [SEALANT](https://softarch.usc.edu/sealant/).

[Mysql Insatallation](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-16-04) on Ubuntu 16.04, if not already installed.

**Step Three**

Clone and import project into eclipse.

**Step Four**

Installing [Mysql++](https://tangentsoft.com/mysqlpp/home)

sudo apt-get install mysql-server mysql-client
sudo apt-get install libmysqlclient-dev libmysql++-dev libmysqlcppconn-dev

Inlcude in libraries
```
/usr/include/mysql++
/usr/include/mysql
```

Add Linkers
```
-lmysqlpp -lmysqlclient
```

**Step Five**

Change information in the following files:

	1. In config.properties:
		a. HOME_FOLDER should be equal to the folder that you saved the project to.
		b. JITANA_IAC location of build/tools/jitana-iac
		c. METHOD_GRAPH_LOCATION location of the output of the method graph.  Location may change depending on usage.
	2. In db/cc.properites:
		a. change user name that matches your database access.
		b. change password attached to name.
		
**Step Six**

Two inputs APKs are currently in folder.  You can change these to match the Applications that you are looking at.

If you are looking for a static analysis then make the METHOD_GRAPH_LOCATION equal to $JITANA_IAC/output and it will use the graph and insn from IAC.




### This project has a fun experience.  I currently do not have plans to contiune working on this, as I will be contiuning work on  [Dwaven Fist](https://bitbucket.org/Totally_Real_Humans/dwarven_fisticuffs/wiki/Home) that I am currently developing for my final project at Drury University.  [Mohannad Alhanahnah](https://github.com/Mohannadcse) will be working on this project, making the system more robust and user friendly.

