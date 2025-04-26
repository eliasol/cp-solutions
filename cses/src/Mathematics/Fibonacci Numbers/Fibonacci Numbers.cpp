#include <iostream>
#include <array>
#include <cstddef>

static constexpr int MOD = 1e9+7;

template<std::size_t N, std::size_t M, std::size_t H>
std::array<std::array<int, H>, N> matrix_prod(std::array<std::array<int, M>, N> A, std::array<std::array<int, H>, M> B) {
	std::array<std::array<int, H>, N> res{};
	for (std::size_t i = 0; i < N; ++i)
		for (std::size_t j = 0; j < H; ++j)
			for (std::size_t k = 0; k < M; ++k)
				res[i][j] = (res[i][j] + (A[i][k] * (long long) B[k][j]) % MOD) % MOD;
	return res;
}

template<std::size_t N>
std::array<std::array<int, N>, N> matrix_exp(std::array<std::array<int, N>, N> a, std::size_t b) {
	std::array<std::array<int, N>, N> res{};
	for (std::size_t i = 0; i < N; ++i)
		res[i][i] = 1;
	while (b) {
		if (b & 1)
			res = matrix_prod(a, res);
		a = matrix_prod(a, a);
		b >>= 1;
	}
	return res;
}

int main() {
	std::array<std::array<int, 2>, 1> a{{ {1, 0} }};
	std::array<std::array<int, 2>, 2> sus {{ {1, 1}, {1, 0} }};

	std::size_t N;
	std::cin >> N;

	std::cout << matrix_prod(a, matrix_exp(sus, N))[0][1] << std::endl;
}
