/* Written in 2015 by Alexander Shishenko <alex@shishenko.com>
 *
 * LVCrypto - Cryptographic wrapper, used in Librevault.
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
#pragma once
#include "Transformer.h"
#include <cryptopp/osrng.h>

namespace librevault {
namespace crypto {

class AES_CBC : public TwoWayTransformer {
private:
	const blob& key;
	const blob& iv;
	bool padding;
public:
	AES_CBC(const blob& key, const blob& iv, bool padding = true);
	virtual ~AES_CBC() {};

	blob encrypt(const blob& plaintext) const;
	blob decrypt(const blob& ciphertext) const;

	static blob random_iv() {
		blob random_iv(16);
		CryptoPP::AutoSeededRandomPool().GenerateBlock(random_iv.data(), random_iv.size());
		return random_iv;
	}

	blob to(const blob& data) const {return encrypt(data);}
	blob from(const blob& data) const {return decrypt(data);}
};

} /* namespace crypto */
} /* namespace librevault */
