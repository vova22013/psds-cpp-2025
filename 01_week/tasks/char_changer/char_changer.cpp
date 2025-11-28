#include <cstddef>
#include <stdexcept>
#include <cctype>

const char a = 'a';
const char A = 'A';
const char dif_letters = static_cast<int>(a) - static_cast<int>(A);

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t count = 1, last_ind = size - 1;
    size_t start_rep_ind, end_rep_ind;

    for (size_t i = 0; i < size; ++i) {

        if (i == size - 1) {
            return last_ind;
        }

        if (array[i] == array[i + 1]) {
            if (count == 1) start_rep_ind = i;
            count++;
            
            if (array[i] == ' ') continue;
        }
        else if (count != 1) {
            end_rep_ind = i + 1;
            i = start_rep_ind;

            size_t ind_next_simbol = i + 2;

            last_ind -= count - 2;

            if (array[i] != ' ') {
                if (count >= 10) array[++i] = '0';
                else array[++i] = static_cast<char>(static_cast<size_t>('0') + count);
            }
            else {
                --ind_next_simbol;
                --last_ind;

                array[i] = delimiter;
            }

            for (size_t j = end_rep_ind; j < size; ++j) {
                std::swap(array[ind_next_simbol], array[j]);
                ++ind_next_simbol;
            }

            size_t reduct_size = end_rep_ind - start_rep_ind;
            size -= reduct_size - 2;

            count = 1;
            
            continue;
        }

        if (static_cast<bool>(std::isdigit(array[i]))) {
            array[i] = '*';
        }
        else if (static_cast<bool>(std::islower(array[i]))) {
            array[i] -= dif_letters;
        }
        else if (static_cast<bool>(std::ispunct(array[i]))) {
            array[i] = '_';
        }
        else if (static_cast<bool>(std::isspace(array[i]))) {
            array[i] = delimiter;
        }
    }

    return last_ind;
}
