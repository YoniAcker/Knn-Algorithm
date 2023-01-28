# Ex4
We submitted the project on Shabbat evening because we had 5 days of grace left, and they said at the beginning of the year that Shabbat does not count (the last day of grace was on Friday, and we had Shabbat left).

In this project we created a client-server lie. The client sends to the network CSV files of classified vectors, and then files of unclassified vectors. The server classifies these vectors according to the KNN algorithm which takes the K vectors closest to the unclassified vector. After the classification, the customer can download the file with the classified vectors to his computer.

We worked with THREAD on the server and the client. on the server, so that it can handle two clients at the same time. And the client, so that when he downloads the file, he can at the same time continue to communicate with the server.

When the client enters "1" he is asked to upload the file with the classified vectors, followed by the unclassified vectors. In case the size of the vectors in the second file are not the same size as the second file, he will receive an error that the file is not correct.

When he enters "2" he can view the settings of the algorithm and change them or leave them. If the K he entered is greater than the number of classified vectors, he will receive an error that K is too large. If he has not yet uploaded the files, then the K will change to be the number of vectors that exist in the file.
In addition, the customer can also change the calculation method of the algorithm.

When the client enters "3", it tells the server to sort the files. If there are no files, it will be printed that he needs to upload files.

When he enters "4" he will get to the screen the vectors after they have been classified. If he has not uploaded files or has not yet asked the server to classify them, an error will be printed to him.

When he enters "5", he will be asked to enter a file to which he will download the classified vectors. If he has not uploaded files or has not yet asked the server to classify them, an error will be printed to him.

The server is operated by a CLI that each client receives, which handles its requests.

We implemented the logic of the server by the COMMANDS design pattern, we created a CLASS of COMMAND which is VIRTUAL. Every action the client can do is defined as a class that inherits from COMMAND. Each one of these needs to execute the "EXECUTE" action, which is to activate the specific action.

Regarding the algorithm itself, we explained in the previous work, we will return briefly:
Each vector is defined to be a NEIGHBOR, which has a TYPE field. The unclassified vectors are defined with an empty TYPE.

Given an unclassified vector, the algorithm calculates the distance (according to different calculation methods) between it and the other classified vectors, and takes the K vectors closest to it. Among them, it finds what is the most common TYPE, and based on that, it defines the TYPE of the new vector.