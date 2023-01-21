make:
	g++ -std=c++11 Server.cpp InputManager.cpp DB.cpp Neighbor.cpp DistanceFuncManager.cpp AlgorithmKnn.cpp  -o server.out
	g++ -std=c++11 Client.cpp InputManager.cpp Neighbor.cpp -o client.out
