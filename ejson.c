/******************************************************************************
                Light Weight json parser for embeddedd systems
                Author: manumadandan@gmail.com
*******************************************************************************/

#include "ejson.h"

/* To find a json attribute */
int ejson_get_attribute(char *json, char *key, char *res){

    int key_index = 0;
    int key_length = strlen(key);
    int processing_index = 0;
    *res = '\0';
    // 1-> Finding the key match for the json
    for(int i=1;i<strlen(json)-1;i++){
        if(key[key_index]==json[i]){
            key_index++;
            // The key match condition
            if(key_index==key_length && (json[i+1]=='\'' || json[i+1]=='\"') 
                                         && (json[i-key_index]=='\'' || json[i-key_index]=='\"')){
                processing_index = i + 1; // for leaving "
                break;
            }
        }else{
            key_index = 0;
        }
    }
    // Nothing to process
    if(processing_index<=0){
        return 0;
    }

    
    //2-> leaving the empty character and the separator :
    for(int i=processing_index + 1;i<strlen(json)-1;i++){
        if(json[i]!=' ' && json[i]!=':'){
            processing_index = i;
            break;
        }
    }
    
    // 3-> finding the actual values 
    char value_starter = json[processing_index];
    int result_index = 0;
    int bracket_counter = 0;
    
    // -> A for string processing [String]
    if(value_starter=='\'' || value_starter=='\"'){
        for(int i=processing_index;i<strlen(json)-1;i++){
            if(i==processing_index){ // start character [remove start ' or "]
                // do nothing
            }else if(json[i]==value_starter){// Close found
                res[result_index] = '\0';
                break;
            }else{// copy
                res[result_index] = json[i];
                result_index++;
                res[result_index] = '\0';
            }
        }
    }
    
    // -> B for string processing [Object] or [Array]
    if(value_starter=='{' || value_starter=='['){
        char value_closser = value_starter + 2; // from ascii table } ]
        for(int i=processing_index;i<strlen(json)-1;i++){
            res[result_index] = json[i];
            result_index++;
            res[result_index] = '\0';
            if(json[i]==value_starter){ // { or [
                bracket_counter++;
            }
            if(json[i]==value_closser){ // ] or }
                bracket_counter--;
            }
            if(bracket_counter==0){
                break;
            }
        }
    }
    
    // -> Numeric value parsing
    if(value_starter>='0' && value_starter<='9'){
        for(int i=processing_index;i<strlen(json)-1;i++){
            if(json[i]>='0' && json[i]<='9'){
                res[result_index] = json[i];
                result_index++;
                res[result_index] = '\0'; 
            }else{
                break;
            }
        }
    }
    return 1;
}

