#include <bits/stdc++.h>
#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <sys/wait.h>
using namespace std; 
  
int main() 
{ 
    
    int n;
    cin >> n;
    std::vector<int> arr(n);
    std::vector<int> brr(n);
    for(int i = 0;i<n;i++){
        cin >> arr[i];
    }
    for(int i = 0;i<n;i++){
        cin >> brr[i];
    }

    // ftok to generate unique key 
    char *pika_args[] = {"python3","code.py",NULL};


    int pid = fork();
    if(pid == 0){
    	key_t key = ftok("shmfile",65); 

    // shmget returns an identifier in shmid 
    int shmid1 = shmget(65528,4096,0666|IPC_CREAT);
    int shmid2 = shmget(65529,4096,0666|IPC_CREAT);
  
    // shmat to attach to shared memory 
    char *a = (char *) shmat(shmid1,(void*)0,0); 
    char *b = (char *) shmat(shmid2,(void*)0,0); 
    
    // create a encoded string to pass to the shared memory
    string string1 = "";

	for(int i = 0;i<n-1;i++){
        string1 += to_string(arr[i]);
        string1 += "a";
    }
    string1 += to_string(arr[n-1]);
    strcpy(a,string1.c_str());

    // another encoded string for the shared memory
    string string2 = "";
    for(int i = 0;i<n-1;i++){
        string2 += to_string(brr[i]);
        string2 += "a";
    }
    string2+= to_string(brr[n-1]);
    strcpy(b,string2.c_str());

    cout << "This string is will be shared memory:" << a  << " " << b << endl;
      
    //detach from shared memory  
    shmdt(a);
    shmdt(b);
    exit(0);
    }
    else{
    	// calling the python program from one of the child processes.
    	// sleep(10);
        wait(NULL);
    	execvp("python3",pika_args);

    }
  
    return 0; 
} 
