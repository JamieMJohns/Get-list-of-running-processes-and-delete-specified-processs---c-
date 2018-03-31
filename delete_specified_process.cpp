/*
code created by jamie johns 2018 using Dev-C++ 5.11
source of code: https://github.com/JamieMJohns/Get-list-of-running-processes-and-delete-specified-processs---c-
code is subject to improvement and optimization
learnt from (for reading task processes): https://msdn.microsoft.com/en-us/library/ms686701(v=vs.85).aspx
store string in vector info: https://www.geeksforgeeks.org/array-strings-c-3-different-ways-create/
*/
#include <windows.h> //include windows.h header file (needed for windows API)
#include <tlhelp32.h> //include tlhelp32.h
#include <tchar.h>	//tchar.h header file	
#include <iostream> //include iostream header file for input/output operations
#include <bits/stdc++.h> //include bits/stdc++.h header file (imports standard operations for c++)
#include <string> //include string header (needed for some string operations)
#include <vector> // include vector header file (need for creating vectors)
#include <algorithm>    // include algorithm header file (needed for operations such as sort)
using namespace std; //use std for namespace
bool compareFunction (std::string a, std::string b); // call to function which sorts strings in alphabetic order (where sorting is applied as if inputs are all lower-case)

int main( ){ // main program @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//system("color 1E"); //change program text to bright yellow coloured 'E' and blue background '1'
	//system("color C"); //change program text to bright red coloured 'C'
	system("color A"); //change program text to bright green coloured 'A'
	// INTRODUCTION STRING #############################################################################################
	cout<<"################################################################################"; // string added for ui purposes
	cout<<"######################### Task Process Terminator ##############################"; // string added for ui purposes
	cout<<"################################################################################"; // string added for ui purposes
	cout<<""<<endl;
	cout<<"                       Program created by                                       "; // string added for ui purposes
	cout<<"                           Jamie M Johns                                        "; // string added for UI purposes
	cout<<"                               2018                                             "; // string added for UI purposes
	cout<<"                     Written in Dev-C++ 5.11                                    "<<endl; // string added for UI purposes
	cout<<"Description:"<<endl; // string added for UI purposes
	cout<<"  This program will list processes currently running on your computer and then  "; // string added for UI purposes
	cout<<"  by entering a process handle name (i.e-'chrome.exe'); the program will kill "<<endl; // string added for UI purposes
	cout<<"  all processes of the same handle name."<<endl; // string added for UI purposes
	cout<<""<<endl; // string added for UI purposes
	system("pause"); // wait for user to press key before continUIng code
	//##################################################################################################################
	cout<<""<<endl;
	cout<<""<<endl;
	int run_this_program=1; //parameter which determines if program will keep running
	while(run_this_program==1){ // while program is running (this section is intended to repeat until user exits program)
		//initialize objects@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		HANDLE hProcessSnap; //create handle identifier for object hprocesssnap
	  	HANDLE hProcess; //create handle identifier for object hprocess
	 	PROCESSENTRY32 pe32; //Describes an entry from a list of the processes residing in the system address space when a snapshot was taken.
	 	DWORD dwPriorityClass; //create dword class dwPriorityClass
	 	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ); //take "snapshot" of processes running
	 	pe32.dwSize = sizeof( PROCESSENTRY32 ); //size of PROCESSENTRY32 [unused]
	 	vector <string> process_name; //initialize vector named "process_name" where each element will be a string (process name)
	 	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
		// record all detetected running processes #######################################
		while( Process32Next( hProcessSnap, &pe32 ) ){ //for each object (pe32) in hprocesssnap [Process32Next runs through processes]
			process_name.push_back(pe32.szExeFile); // add process name to list of processes		
		};
		//##################################################################################
		// Get list of unique process names and number of times that process name has process$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		vector <string> process_name_unique; //initialize vector of string elements (each element will be unique process name)
		vector <int> process_num_occur; //initialize vector of integer elements (each element will be count that unique process has occured)
		process_name_unique.push_back(process_name[3]); //initialise first process; start from 3 [0=blank 1='sys' var 2=another title 3=first process listed]
		process_num_occur.push_back(1); //initialise count for first process
		for(int k=3;k<=process_name.size()-1;k++){ // for each kth process name in complete list
			int add_unique=1; //initialise parameter that tells if proccess is unique (=1)
			for(int j=0;j<=process_name_unique.size()-1;j++){ // for each jth process in list of unique process names
				string st1=process_name[k]; //string 1 = process name from complete list (k)
				string st2=process_name_unique[j]; // process name from unique list (j)
				if(strcmp(st1.c_str(),st2.c_str())==0 && add_unique==1 ){ //if process names j&k match and if unique parameter=1 [c_str() converts cmmdtsk to c string, needed for strcmp]
																		  // note: str(a,b)=0 if string a and b are identical match
					process_num_occur[j]+=1; //add to count for re-occurance of process name
					add_unique=0; //set unique process parameter to 0 [process name from list k is already in list j]
				}; // if loop
			};  // for loop (j)
			if(add_unique==1){ //if process name from list k was unique (to be added to list)
				process_name_unique.push_back(process_name[k]); //add process name from list k to list of unique process
				process_num_occur.push_back(1);	 //initialise count of occurance for newly added process name
			}; // if loop
		};// for loop (k)
		//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		
		// sort process name alphabetically and then also sort "num occurance" accordingly&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		vector <string> process_name_unique_unsorted; //initialize vector that will be unsorted vector of process names;
		vector <int> process_num_occur_sorted; //initialize vector that will be unsorted vector of process names;
		for(int k=0;k!=process_name_unique.size();k++) process_name_unique_unsorted.push_back(process_name_unique[k]); //add elements from original list to new list [for loop in one line]
		std::sort(process_name_unique.begin(),process_name_unique.end(),compareFunction); // sortvector using compare function (output is that process_name_unique is sorted alphabetically using function "compareFunction")
		// sort process_num_occur alphabetically and as new vector "process_num_occur_sorted" (previously initialized but is still empty@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for(int k=0;k!=process_name_unique.size();k++) for(int j=0;j!=process_name_unique.size();j++){ // for each element of sorted(k) and unsorted (j) for process name [Double for loop defined in one line]
			if(strcmp(process_name_unique[k].c_str(),process_name_unique_unsorted[j].c_str())==0) process_num_occur_sorted.push_back(process_num_occur[j]); //if string of kth string (sorted) and jth string (unsorted) match;
		};                                                                                                                                                  //then, add jth process_num_occur element to new list
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
		
		// Print unique processes %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		cout<<"Processes that are running$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl; // string added for UI purposes
		cout<<"PROCESS NAME || Number of processes of same name                                "<<endl; // string added for UI purposes
		for(int k=0;k<=(process_name_unique.size()-1);k++){ // for each kth element in sorted list of process names
			cout<<process_name_unique[k]; // print kth process name
			cout<<" || "<<process_num_occur_sorted[k]<<endl; // print number of occurances for kth process name (also previously assorted correspondingly with vector above)
		};
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl; // string added for UI purposes
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
		cout<<"ABOVE: list of names of processes that are currently running, along with number"<<endl; // string added for UI purposes
		cout<<"        of occurances for handle name."<<endl; // string added for UI purposes
		cout<<""<<endl; // string added for UI purposes
		string p2t; // initialise string which will process handle name of process/s to terminate (user will define this below)
		cout<<"Below, enter the name of the process that you want to terminate;"<<endl; // string added for UI purposes
		cout<<"for example, enter 'chrome.exe' to terminate all processes of that handle name."<<endl; // string added for UI purposes
		cout<<"(exit the program if you do not wish to progress)"<<endl; // string added for UI purposes
		cout<<""<<endl; // string added for UI purposes
		cout<<"Process (name) to terminate:"; // string added for UI purposes
		cin>>p2t; // [USER INPUT FOR PROCESS NAME HANDLE OF PROCESSES/S TO TERMINATE]
		std::string namep = p2t; //convert p2t to string for use below (had to this for system() to work, yet to be optimized from this)
		std::string cmmdtsk="taskkill /IM "+namep+" /F"; //create full string to run in line below (had to this for system() to work, yet to be optimized from this)
		system(cmmdtsk.c_str()); //c_str() converts cmmdtsk to c string
		cout<<""<<endl; // string added for UI purposes
		cout<<""<<endl; // string added for UI purposes
		cout<<"<PRESS ENTER TO GET UPDATED LIST OF RUNNING PROCESSES (the program will re-run)>."<<endl; // string added for UI purposes
		cout<<"Otherwise, exit the program if you are finished."; // string added for UI purposes
		system("pause"); // wait for user response
	}; // end of whileloop (goes back to beginning unless user exits the program
	return 0; //used when compiling in c++; prints zero if program compiled/ran with no errors
}// end of main program @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


bool compareFunction (std::string a, std::string b){ //function for sorting strings (of vector) in alphabetic order [considering them as lower-case]
	for(int k=0;k<=a.size()-1;k++){ // convert each element in vector a (string) to lower case
		a[k]=tolower(a[k]); //convert kth element of vector a to lower case
	};
	for(int k=0;k<=b.size()-1;k++){ // convert each element in vector b (string) to lower case
		b[k]=tolower(b[k]); //convert kth element of vector b to lower case
	};
	return a<b; // return a<b (sorted)
};
