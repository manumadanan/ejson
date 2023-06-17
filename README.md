# ejson
Lightweight Json specially for embedded systems

<pre>
char json_str[] = "{\"Name\":\"Manu\", \"Age\":100, \"Details\":{\"address\":\"kollam\", \"phone\":101}}";
int main(){
   char key[] = "Details";
   char key_ph[] = "phone";
   char res1[500];
   char res2[10]; 
   ejson_get_attribute(json_str, key, res1);
   printf("Details: [%s]\r\n", res1);
   ejson_get_attribute(res1, key_ph, res2);
   printf("Phone: [%s]\r\n", res2);
}
</pre>
