/*
 * This file is part of the SpinBits distribution Copyright (c) 2018
 * Jimmy Aguilar Mena.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>

typedef class spin {
	private:
		int val : 2;
	public:
		spin(const bool v = true) : val(v ? 1 : -1) {};
		spin(const int v) : val(v > 0 ? 1 : -1) {};
		explicit operator bool() const { return (val > 0 ? true : false); }
		operator int() const { return int(val); }
} spin_t;


template<std::size_t N>
class spinset {
	private:
		std::bitset<N * N> data;

	public:
		spinset(bool random = false) : data(0) {
			if (random){
				std::random_device rd;  //Will be used to obtain a seed for the random number engine
				std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
				std::uniform_int_distribution<> dis(0, 1);
				for (size_t i = 0; i < N; ++i)
					for (size_t j = 0; j < N; ++j)
						data[i * N + j] = dis(gen);
			}
		}

		// Get values
		const spin_t get(const size_t i, const size_t j) const {
			assert(i < N && j < N);
			return spin_t(data[ i * N + j ]);
		}

		void set(const size_t i, const size_t j, spin_t value) {
			assert(i < N && j < N);
			data[ i * N + j ] = bool(value);
		}

		// toggle all or individual bits
		void flip(const size_t i, const size_t j) {
			assert(i < N && j < N);
			data.flip(i * N + j);
		}
		void flip() { data.flip(); }

		// Get number of values
		size_t size(){ return N; }

		operator std::string() const {
			std::string out = "\n";
			for (std::size_t i = 0; i < N; ++i) {
				out += "[";
				for (std::size_t j = 0; j < N; ++j) {
					out += data[i * N + j] ? "+1 " : "-1 ";
				}
				out += "]\n";
			}
			return out;
		}

};

template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const spinset<N>& in)
{
	os << std::string(in);
	return os;
}

using namespace std;
int main()
{
	spinset<16> set(true);

	cout << "Random array" << endl;
	cout << set << endl;

	for (size_t i = 0; i < 16; ++i)
		set.set(i, 0, 1);
	cout << "Random column +1" << endl;
	cout << set << endl;

	for (size_t i = 0; i < 16; ++i)
		set.set(0, i, -1);
	cout << "Random row -1" << endl;
	cout << set << endl;

	set.flip();
	cout << "Flip" << endl;
	cout << set << endl;

	cout << "Sizes comparison" << endl;
	cout << "With bitset: " << sizeof(set) << endl;
	cout << "With int array: " << (16 * 16 * sizeof(int)) << endl;

	return 0;
}
