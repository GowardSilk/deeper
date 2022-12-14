#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "DeepMain.hpp"
//#include "Shadow.hpp"

template<typename T1, typename T2>
class Shadow_prcl;

namespace wrd {
	enum class _TERMINAL_ {
		T_DISCONNECTED, A_220, B, C, D, E
	};
	class Terminal_prcl {
		private:
			//terminal type
			wrd::_TERMINAL_ terminal_type = _TERMINAL_::T_DISCONNECTED;
			//evaluation of (expressed in %) test success rate 
			float terminal_hack_success = 0.f;
			//
			template<typename T1, typename T2>
			friend class Shadow_prcl;
		protected:
			bool is_shadowed = false;
		public:
			void hijack(triplet<int> (*func)(triplet<int>)) {
				if(!is_shadowed) {
					switch(terminal_type) {
						/*
						ANS HERE!!!
						https://stackoverflow.com/questions/11034759/different-types-assignment-in-switch-state-cases-inside-template-function
						*/
						//check if usr is connected
						case _TERMINAL_::T_DISCONNECTED:
						{	//
							std::cout << "not connected!\n";
							exit(EXIT_FAILURE);
							break;
						}
						//
						case _TERMINAL_::A_220:
						{	//
							std::ifstream rf("Terminal1.dat", std::ios::out | std::ios::binary);
							if(!rf) {
								std::cout << "cannot read file!\n";
							}
							//TEST CASES
							for(unsigned i = 0; i < 10; i++) {
								triplet<int> input;
								rf.read((char*) &input, sizeof(triplet<int>));

								triplet<int> tr_expected;
								rf.read((char*) &tr_expected, sizeof(triplet<int>));

								if(tr_expected == func(input))
									this->terminal_hack_success += 0.1f;

								if(!rf.good()) {
									std::cout << "error occurred at reading time!\n";
								}
							}
							//!TEST_CASES
							rf.close();
							break;
						}
						//
						case _TERMINAL_::B:
						{	//
							std::ifstream rf("Terminal2.dat", std::ios::out | std::ios::binary);
							if(!rf) {
								std::cout << "cannot read file!\n";
							}
							//TEST_CASES
							for(unsigned i = 0; i < 10; i++) {
								triplet<int> input;
								rf.read((char*) &input, sizeof(triplet<int>));

								triplet<int> tr_expected;
								rf.read((char*) &tr_expected, sizeof(triplet<int>));

								if(tr_expected == func(input))
									this->terminal_hack_success += 0.1f;

								if(!rf.good()) {
									std::cout << "error occurred at reading time!\n";
								}
							}

							//!TEST_CASES
							rf.close();
							break;
						}
						default:
							std::cout << "No Terminal matches the arguments list!\n";
							break;
					}
				}
			}
			void hijack(triplet<int> (*func)(TripletContainer<int>)) {
				if(!is_shadowed) {
					switch (this->terminal_type)
					{
						//check if usr is connected
						case _TERMINAL_::T_DISCONNECTED:
						{	//
							std::cout << "not connected!\n";
							exit(EXIT_FAILURE);
							break;
						}
						//
						case _TERMINAL_::C:
						{	//
							std::ifstream rf("Terminal3.dat", std::ios::out | std::ios::binary);
							if(!rf) {
								std::cout << "cannot read file!\n";
							}
							//TEST_CASES
							for(unsigned i = 0; i < 10; i++) {
								TripletContainer<int> tr_con_input;
								for(unsigned i = 0; i < 5; i++) {
									triplet<int> tr_temp;
									rf.read((char*) &tr_temp, sizeof(triplet<int>));
									tr_con_input.push_back(tr_temp);
								}

								triplet<int> tr_expected;
								rf.read((char*) &tr_expected, sizeof(triplet<int>));

								if(tr_expected == func(tr_con_input))
									this->terminal_hack_success += 0.1f;

								if(!rf.good()) {
									std::cout << "error occurred at reading time!\n";
								}

							}
							//!TEST_CASES
							rf.close();
							break;
						}
						default:
							std::cout << "No Terminal matches the arguments list!\n";
							break;
					}
				}
			}
			void hijack(int (*func)(TripletContainer<int>)) {
				if(!is_shadowed) {
					switch (this->terminal_type)
					{
					case _TERMINAL_::T_DISCONNECTED:
						std::cout << "not connected!\n";
						exit(EXIT_FAILURE);
						break;
					case _TERMINAL_::D:
					{	//
						std::ifstream rf("Terminal4.dat", std::ios::out | std::ios::binary);
						if(!rf) {
							std::cout << "cannot read file!\n";
						}
						//TEST_CASES
						for(unsigned i = 0; i < 10; i++) {
							TripletContainer<int> tr_con_input;
							for(unsigned i = 0; i < 5; i++) {
								triplet<int> tr_temp;
								rf.read((char*) &tr_temp, sizeof(triplet<int>));
								tr_con_input.push_back(tr_temp);
							}

							int expected;
							rf.read((char*) &expected, sizeof(int));

							if(expected == func(tr_con_input))
								this->terminal_hack_success += 0.1f;

							if(!rf.good()) {
								std::cout << "error occurred at reading time!\n";
							}

						}
						//!TEST_CASES
						rf.close();
						break;
					}
					default:
						break;
					}
				}
			}
			void hijack(TripletContainer<int> (*func)(TripletContainer<int>)) {
				if(!is_shadowed) {
					switch (this->terminal_type)
					{
					case _TERMINAL_::T_DISCONNECTED:
						std::cout << "not connected!\n";
						exit(EXIT_FAILURE);
						break;
					case _TERMINAL_::E:
						break;
					default:
						break;
					}
				}
			}
			void override() {
				if(!is_shadowed)
					std::cout << this->terminal_hack_success*100 << "%" << std::endl;
			}
			void connect(wrd::_TERMINAL_ terminal) {
				this->terminal_type = terminal;
			}
	};
} //!namespace Warden

#endif