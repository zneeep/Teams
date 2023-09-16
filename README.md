# Teams
This a C version of Microsoft Teams application.  
  
This project had to be done by groups of 2 people.  
  
The call functionnality is not included. However, you still can create users, teams, channels, send messages, give access and rights to whoever you want on the channels/teams you created, create posts and answer to those.  
  
We had to implement a database so that the already existing users are saved when the program is stopped.  
  
If you want to test it , here are the steps for compilation and usage :  
 1- Clone the repository using Git  
 2- Compile the program using the command "make" at the root of the repository  
 3- Use the following command at the root of the repository : export LD_LIBRARY_PATH=/libmyteams:$LD_LIBRARY_PATH  
 4- Launch the my_teams server using the command "./myteams_server port" and replace port by the port number you want the server to listen to.  
 5- Launch as many clients you want in other terminals by using "./myteams_cli ip port" and replace the IP by the IP adress of the server you launched (127.0.0.1 if the server is running locally),     then replace the port by the port number you want your client to use/listen to. DON'T FORGET TO DO STEP 3 FOR EVERY TERMINAL YOU'RE LAUNCHING THE CLIENT ON.  
 6- Use the following commands as a client, notifications are triggered on the client side or on the server side for each command used :  
       • /login [“user_name”] : set the user_name used by client -> connect to the server as user_name  
       • /logout : disconnect the client from the server  
       • /send [“user_uuid”] [“message_body”] : send a message to specific user  
       • /messages [“user_uuid”] : list all messages exchanged with the specified user  
       • /subscribe [“team_uuid”] : subscribe to the events of a team and its sub directories (enable reception of all events from a team)  
       • /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team  
       • /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the command context to a team/channel/thread  
       • /create : based on the context, create the sub resource (see below)  
       • /list : based on the context, list all the sub resources (see below)  
_____________________________________________________________________________________________________________________________________________________________________________________________________       
        /CREATE
          When the context is not defined (/use):
          • /create [“team_name”] [“team_description”] : create a new team
          When team_uuid is defined (/use “team_uuid”):
          • /create [“channel_name”] [“channel_description”] : create a new channel
          When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
          • /create [“thread_title”] [“thread_message”] : create a new thread
          When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
          • /create [“comment_body”] : create a new reply
       /LIST
          When the context is not defined (/use):
          • /list : list all existing teams
          When team_uuid is defined (/use “team_uuid”):
          • /list : list all existing channels
          When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
          • /list : list all existing threads
          When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
          • /list : list all existing replies
