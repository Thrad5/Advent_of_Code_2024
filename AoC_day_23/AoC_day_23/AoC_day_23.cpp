// AoC_day_23.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <queue>

class Graph {
	std::map<std::string,std::set<std::string>> adj_lst;
public:
	void add_edge(std::string first, std::string second) {
		adj_lst[first].insert(second);
		adj_lst[second].insert(first);
	}

	void print() {
		std::cout << "Adjacency list for the Graph: \n";
		for (auto i : adj_lst) {
			std::cout << i.first << "-> ";
			for (auto j : i.second) {
				std::cout << j << " ";
			}
			std::cout << "\n";
		}
	}
	void find3Cycle() {
		std::vector<std::vector<std::string>> cycles;
		for (auto first_vert : adj_lst) {
			//Gets first vertex
			std::cout << first_vert.first << " ";
			for (auto second_vert : first_vert.second) {
				//get second vertex
				//get list of vertecies attached to first vertex
				auto second_vert_list = adj_lst[second_vert];
				for (auto third_vert : second_vert_list) {
					//get third vertex
					if (first_vert.first != third_vert && adj_lst[first_vert.first].contains(third_vert) && (first_vert.first[0] == 't' || second_vert[0] == 't' || third_vert[0] == 't')) {
						cycles.push_back({ first_vert.first,second_vert,third_vert });
					}
				}
			}
		}
		std::cout << "\n";
		//std::cout << "Cycles of 3 vertecies are: \n";
		std::cout << "There are " << cycles.size()/6 << " loops.\n";
	}
	void findMaxConnectd() {
		std::set<std::set<std::string>> cliques;
		std::set<std::string> glob_seen;
		for (auto [a, _] : adj_lst) {
			if (glob_seen.contains(a)) {
				continue;
			}
			std::queue<std::string> to_visit;
			to_visit.push(a);
			std::set<std::string> clique,seen_in_clique;
			while (to_visit.size() != 0) {
				auto checking = to_visit.front();
				to_visit.pop();
				if (seen_in_clique.contains(checking)) { continue; }
				seen_in_clique.insert(checking);
				bool connected = true;
				for (auto test : clique) {
					if (checking != test && !adj_lst[test].contains(checking)) {
						connected = false;
					}
				}
				if (connected) {
					clique.insert(checking);
					for (auto to_add : adj_lst[checking]) {
						to_visit.push(to_add);
					}
				}
			}
			for (auto seen : clique) {
				glob_seen.insert(seen);
			}
			cliques.insert(clique);
		}
		std::set<std::string> max_clique;
		for (auto cl : cliques) {
			if (cl.size() > max_clique.size()) {
				max_clique = cl;
			}
		}
		std::cout << "\n";
		for (auto ls : max_clique) {
			std::cout << ls << ",";
		}
	}
	bool x_in_y(std::vector<std::string> x, std::vector<std::vector<std::string>> y) {
		for (std::vector<std::string> r : y) {
			//std::cout << r[0] << " " << r[1] << " " << r[2] << "\n";
			//std::cout << x[0] << " " << x[1] << " " << x[2] << "\n";
			if ((r[0] == x[0] && r[1] == x[1] && r[2] == x[2]) || (r[0] == x[0] && r[1] == x[2] && r[2] == x[1]) || 
				(r[0] == x[1] && r[1] == x[0] && r[2] == x[2]) || (r[0] == x[1] && r[1] == x[2] && r[2] == x[0]) ||
				(r[0] == x[2] && r[1] == x[0] && r[2] == x[1]) || (r[0] == x[2] && r[1] == x[1] && r[2] == x[0])) {
				return true;
			}
		}
		return false;
	}
	int vert_length() {
		return adj_lst.size();
	}
};

int main()
{
	Graph g;
	std::fstream file;
	std::string tp;
	file.open("D:\\!Advent_of_Code\\2024\\AoC_day_23\\input.txt");
	while (getline(file, tp)) {
		std::string first = tp.substr(0, 2);
		std::string second = tp.substr(3, tp.npos);
		g.add_edge(first, second);
	}
	file.close();
	g.print();
	std::cout << "Completed the Graph. There are "<< g.vert_length() <<" verticies.\n";
	g.find3Cycle();
	g.findMaxConnectd();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
