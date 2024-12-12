#pragma once
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdlib>
#include <cstdint>
#include <string>

namespace detail
{
	template <typename Type, Type OffsetBasis, Type Prime>
	struct size_dependant_data
	{
		using type = Type;
		constexpr static auto k_offset_basis = OffsetBasis;
		constexpr static auto k_prime = Prime;
	};

	template <size_t Bits>
	struct size_selector;

	template <>
	struct size_selector<32>
	{
		using type = size_dependant_data<std::uint32_t, 0x811c9dc5ul, 16777619ul>;
	};

	template <>
	struct size_selector<64>
	{
		using type = size_dependant_data<std::uint64_t, 0xcbf29ce484222325ull, 1099511628211ull>;
	};

	// Implements FNV-1a hash algorithm
	template <std::size_t Size>
	class fnv_hash
	{
		using data_t = typename size_selector<Size>::type;

	public:
		using hash = typename data_t::type;

	private:
		constexpr static auto k_offset_basis = data_t::k_offset_basis;
		constexpr static auto k_prime = data_t::k_prime;

	public:
		template <std::size_t N>
		static __forceinline constexpr auto hash_constexpr(const char(&str)[N], const std::size_t size = N) -> hash
		{
			return static_cast<hash>(1ull * (size == 1
				? (k_offset_basis ^ str[0])
				: (hash_constexpr(str, size - 1) ^ str[size - 1])) * k_prime);
		}

		template <std::size_t N>
		static __forceinline constexpr auto hash_constexpr(const wchar_t(&str)[N], const std::size_t size = N) -> hash
		{
			return static_cast<hash>(1ull * (size == 1
				? (k_offset_basis ^ str[0])
				: (hash_constexpr(str, size - 1) ^ str[size - 1])) * k_prime);
		}

		static auto __forceinline hash_runtime(const char* str) -> hash
		{
			auto result = k_offset_basis;
			do
			{
				result ^= *str++;
				result *= k_prime;
			} while (*(str - 1) != '\0');

			return result;
		}
		static auto __forceinline hash_runtime_lower(const char* str) -> hash
		{
			auto result = k_offset_basis;
			do
			{
				result ^= tolower(*str++);
				result *= k_prime;
			} while (*(str - 1) != '\0');

			return result;
		}


		static auto __forceinline hash_runtime(const std::string& in_str) -> hash
		{
			auto result = k_offset_basis;
			char* str = const_cast<char*>(in_str.data());
			do
			{
				result ^= *str++;
				result *= k_prime;
			} while (*(str - 1) != '\0');

			return result;
		}

		static auto __forceinline hash_runtime_lower(const wchar_t* str) -> hash
		{
			auto result = k_offset_basis;
			do
			{
				result ^= tolower(*str++);
				result *= k_prime;
			} while (*(str - 1) != L'\0');

			return result;
		}

		static auto __forceinline hash_runtime(const wchar_t* str) -> hash
		{
			auto result = k_offset_basis;
			do
			{
				result ^= *str++;
				result *= k_prime;
			} while (*(str - 1) != L'\0');

			return result;
		}

		static __forceinline constexpr auto hash_init(
		) -> hash
		{
			return k_offset_basis;
		}

		static __forceinline constexpr auto hash_byte(
			hash current,
			std::uint8_t byte
		) -> hash
		{
			return (current ^ byte) * k_prime;
		}

		static auto __forceinline hash_runtime_data(
			const void* data,
			const std::size_t sz
		) -> hash
		{
			const auto bytes = static_cast<const uint8_t*>(data);
			const auto end = bytes + sz;
			auto result = hash_init();
			for (auto it = bytes; it < end; ++it)
				result = hash_byte(result, *it);

			return result;
		}
	};
}

using fnv = detail::fnv_hash<sizeof(void*) * 8>;

#define FNV(str) (std::integral_constant<fnv::hash, fnv::hash_constexpr(str)>::value)