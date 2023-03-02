#include "../Include/review.h"


struct review
{
    char *review_id;
    char *user_id;
    char *business_id;
    float stars;
    int useful;
    int funny;
    int cool;
    char*date;
    char*text;
};

void printReview (Review review){
    printf("Review_id:%s\n",review->review_id);
    printf("User_id:%s\n",review->user_id);
    printf("Business_id:%s\n",review->business_id);
    printf("Stars:%f\n",review->stars);
    printf("Useful:%d\n",review->useful);
    printf("Funny:%d\n",review->funny);
    printf("Cool:%d\n",review->cool);
    printf ("Date:%s\n",review->date);
    printf("Text:%s\n",review->text);
}

Review initReview (char *review_id,char *user_id,char *business_id,float stars,int useful,int funny,int cool,char* date,char*text){
    Review review = malloc (sizeof (struct review));
    review->review_id = strdup (review_id);
    review->user_id = strdup (user_id);
    review->business_id = strdup (business_id);
    review->stars = stars;
    review->useful = useful;
    review->funny = funny; 
    review->cool = cool;
    review->date = strdup (date); 
    review->text = strdup (text);
    return review;
}

void freeReview (void *data){
    Review rev = (Review)data;
    free (rev->review_id);
    free (rev->user_id);
    free (rev->business_id);
    free (rev->date);
    free (rev->text);
    free (rev);
}

//GETTERSS

Review strToReview (char *line){
    char *review_id = strtok (line,";");
    char *user_id = strtok (NULL,";");
    char *business_id = strtok (NULL,";");
    float stars = atof (strtok (NULL,";"));
    int useful = atoi (strtok (NULL,";"));
    int funny = atoi (strtok (NULL,";"));
    int cool = atoi (strtok (NULL,";"));
    char *date = strtok (NULL,";");
    //int year = atoi (strtok (NULL,"-"));
    //int month = atoi (strtok (NULL,"-"));
    //int day = atoi (strtok (NULL," "));
    //int hour = atoi (strtok (NULL,":"));
    //int minutes = atoi (strtok (NULL,":"));
    //int seconds = atoi (strtok (NULL,";"));
    //Date date = newDate (year, month,day,hour,minutes,seconds);
    char *text = strtok (NULL,"\n");
    Review review = initReview (review_id,user_id,business_id,stars,useful,funny,cool,date,text);
    return review;
}

char* Rget_review_id (Review review){
    return strdup(review->review_id);
}

char* Rget_user_id (Review review){
    return strdup(review->user_id);
}

char* Rget_business_id (Review review){
    return strdup(review->business_id);
}

float Rget_stars (Review review){
    return review->stars;
}

int Rget_useful (Review review){
    return review->useful;
}

int Rget_funny (Review review){
    return review->funny;
}

int Rget_cool (Review review){
    return review->cool;
}

char* Rget_date (Review review){
    return strdup(review->date);
}

char* Rget_text (Review review){
    return review->text;
}
