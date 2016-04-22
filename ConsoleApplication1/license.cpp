#include "stdafx.h"
#include "license.h"
#include <math.h>
#include <algorithm>

using namespace cro;

license::license(){}
license::license(const string& _seed, const string& _format){ init(_seed, _format); }
license::~license(){}

bool license::init(const string& _seed, const string& _format)
{
	for (size_t i = 0; i < _seed.length(); ++i) {
		// 키테이블에 없는 시드값을 사용시 에러처리!!
		if (mKeyTable.length() <= mKeyTable.find(_seed[i])) {
			return false;
		}
	}
	mSeed = _seed;
	mCounts.clear();

	// 라이센스 형식
	size_t	charCnt = 0,
			tmpCnt  = 0;

	for (size_t i = 0; i < _format.length(); ++i) {
		if ('-' == _format[i]) { // 구분자 확인
			if (2 > charCnt) { // 잘못된 형식 체크 ex) XXX-[]-[X]-XX ※2자리수 이상이어야 사용
				mCounts.clear();
				return false;
			}
			mCounts.push_back(charCnt);
			charCnt = 0;
			++tmpCnt;
		}
		else {
			++charCnt;
		}
	}
	mCounts.push_back(charCnt);
	return true;
}

bool license::getLicense(const string& _seed, const string& _format, const size_t _index, string& retLicense) 
{

}

bool license::getLicense(const size_t _index, string& retLicense)
{
	// 초기화 실패여부 체크
	if (mCounts.empty()) { return false; }

	// 구분자리별 최대 개수 산출
	vector<size_t> maxCounts(mCounts.size());
	size_t cnt=0;
	for (size_t i = mCounts.size()-1; i < mCounts.size(); --i) {
		cnt += ( mCounts[i] - 1 );
		maxCounts[i] = static_cast<size_t>(pow(mKeyTableLen, cnt));
	}
	if (_index >= maxCounts[0]) { // 최대 개수 초과시 취소처리
		return false;
	}

	// 키생성
	size_t targetIdx = _index;
	string tmpKey;
	for (size_t i = mSeed.length()-1; i < mSeed.length(); --i) {

		const size_t _tmpMax = static_cast<size_t>(pow(mKeyTableLen, mCounts[i]-1));
		
		// 인덱스 시작값 보정 산출공식( √구분자리최대값 * 시드테이블인덱스값 )
		const size_t _offset = static_cast<size_t>(sqrt(_tmpMax)) * mKeyTable.find(mSeed[i]);
		
		const size_t _tmpIdx = (_offset + targetIdx) % _tmpMax;
		targetIdx /= _tmpMax;

		tmpKey.clear();
		getKeyFromIndex(tmpKey, _tmpIdx, mCounts[i]);
		
		tmpKey += getCheckSum(tmpKey, mSeed[i]); // 마지막자리에 체크섬 추가

		if (i != mSeed.length() - 1) {
			retLicense = '-' + retLicense; // 구분자(-) 삽입
		}
		retLicense = tmpKey + retLicense;
	}

	return true;
}


void license::getKeyFromIndex(string& retKey, size_t idx, const size_t _maxLen)
{
	retKey = mKeyTable[idx % mKeyTableLen] + retKey;
	idx /= mKeyTableLen;
	if (idx == 0) {
		while (retKey.length() < _maxLen-1) { // 여백 채우기
			retKey = mKeyTable[0] + retKey;
		}
		return;
	}
	getKeyFromIndex(retKey, idx, _maxLen);
}

char license::getCheckSum(const string& _key, const char _seed)
{
	size_t seedIdx = mKeyTable.find(_seed);

	size_t keySum = 0;
	for (size_t i = 0; i < _key.length(); ++i) {
		keySum += mKeyTable.find(_key[i]);
	}
	keySum %= mKeyTableLen;

	return mKeyTable[ keySum <= seedIdx ? seedIdx-keySum : mKeyTableLen-keySum+seedIdx ];
}

bool license::checkLicense(const string& _license, string& retSeed)
{
	return true;
}
