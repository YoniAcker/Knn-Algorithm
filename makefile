make:
	g++ -pthread -g -std=c++11 Server.cpp Display.cpp DB.cpp Change.cpp Classify.cpp CLI.cpp Command.cpp SocketIO.cpp Download.cpp StandardIO.cpp Update.cpp InputManager.cpp  Neighbor.cpp DistanceFuncManager.cpp AlgorithmKnn.cpp -o server.out

	g++ -pthread -g -std=c++11 Client.cpp Display.cpp DB.cpp Change.cpp Classify.cpp CLI.cpp Command.cpp SocketIO.cpp Download.cpp StandardIO.cpp Update.cpp InputManager.cpp  Neighbor.cpp DistanceFuncManager.cpp AlgorithmKnn.cpp -o client.out
