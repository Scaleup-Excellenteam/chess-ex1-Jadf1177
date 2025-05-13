#include "Move.h"

/**
 * @brief Overloaded output stream operator for the Move class.
 *
 * This function prints the details of a Move object to the provided output stream.
 *
 * @param os The output stream to print to.
 * @param move The Move object to print.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Move& move) {
    /*os << "Move from (" << char(move.fromRow+'a') << ", " << move.fromCol + 1 << ") to ("
        << char(move.toRow+'a') << ", " << move.toCol + 1 << ") with score " << move.score;*/

    os << "recommended move : " << char(move.fromRow + 'a') << move.fromCol + 1 << " to "
        << char(move.toRow + 'a') << move.toCol + 1 ;
    return os;
}
