#include "../Include/user.h"

struct user{
	char *User_id;
	char *name;
	GPtrArray* friends;
    int numFriends;
};


//Free

void freeUser (void * data){
    User user = (User) data;
    free (user->User_id);
    free (user->name);
    g_ptr_array_free (user->friends,TRUE);//free array but not the content
    free (user);
}

//Constructor

User initUser (char * User_id, char * name, GPtrArray * friends,int numFriends){
    User new_user = malloc (sizeof (struct user));
    new_user->User_id = strdup (User_id);
    new_user->name = strdup (name);
    new_user->numFriends = numFriends;
    new_user->friends = friends;
    return new_user;
}


User strToUser (char * line,int with_friends){
    char *userId = strtok (line,";");
    char *name = strtok (NULL,";");
    GPtrArray * array = g_ptr_array_new_with_free_func (free);
    int numFriends = 0;
    if (with_friends){
        char * friend;
        while ((friend = strtok (NULL,","))){
            char *add = strdup (friend);
            g_ptr_array_add (array,add);
            numFriends++;
        }
    }
    User user = initUser (userId,name,array,numFriends);
    return user;
}

//Getter

char* Uget_user_id (User user){
    return strdup(user->User_id); 
}

char* Uget_name (User user){
    return strdup(user->name);
}

GPtrArray* Uget_friends (User user){
    return user->friends;
}

int Uget_numFriends (User user){
    return user->numFriends;
}
