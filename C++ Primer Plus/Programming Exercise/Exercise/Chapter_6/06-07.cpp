#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int main07(){
	string word;
	int vowel_num{}, consonant_num{}, other_num{};

	cout << "Enter words (q to quit):" << endl;
	while (cin >> word && word != "q")
	{
		if (isalpha(word[0])) {
			switch (word[0])
			{
			case 'a':
			case 'i':
			case 'u':
			case 'e':
			case 'o':
				vowel_num++;
				break;
			default:
				consonant_num++;
				break;
			}
		}
		else {
			other_num++;
		}
	}
	cout << vowel_num << " words beginning with vowels" << endl;
	cout << consonant_num << " words beginning with consonants" << endl;
	cout << other_num << " others" << endl;

	return 0;
}