#pragma once

#include <string>
#include <vector>
using namespace std;

namespace cro {

	class license
	{
	protected:
		// shuffle letters : http://jsfiddle.net/9L8rs/5/
		const string	mKeyTable		= "FJB5G6Z4N7WHSYAVMU2TQLX3DKR8P9CE";// "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
		const size_t	mKeyTableLen	= mKeyTable.length(); // ex) length:32

		string			mSeed	= "";
		vector<size_t>	mCounts; // ex) [2,3,4] = XX-XXX-XXXX


		void			getKeyFromIndex(string& retKey, size_t idx, const size_t _maxLen);

		char			getCheckSum(const string& _key, const char _seed);

	public:
		static bool		getLicense	(const string& _seed, const string& _format, const size_t _index, string& retLicense);
		static bool		checkLicense(const string& _license, string& retSeed);

		bool			init		(const string& _seed, const string& _format);
		bool			getLicense	(const size_t _index, string& retLicense);

		const string&	getSeed		() { return mSeed; }

		license();
		license(const string& _seed, const string& _format); // seed:ABC, format:"XXX-XXX-XXXXX" 탬플릿 구조랑 시드값 개수가 일치해야함!!
		virtual ~license();
	};
}
