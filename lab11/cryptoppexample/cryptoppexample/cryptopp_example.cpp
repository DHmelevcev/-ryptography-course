#include "cryptopp_example.h"

using namespace CryptoPP;

void cryptoppexample::symmetric_chipher_dechipher(std::string filename)
{
	AutoSeededRandomPool rng(true);
	byte key[AES::MAX_KEYLENGTH];
	byte iv[AES::BLOCKSIZE];
	rng.GenerateBlock(key, sizeof(key));
	rng.GenerateBlock(iv, sizeof(iv));
	CFB_Mode<AES>::Encryption Encryptor(key, sizeof(key), iv);

	FileSource(
		filename.c_str(),
		true,
		new StreamTransformationFilter(
			Encryptor,
			new FileSink((filename + "_encoded.txt").c_str())
		)
	);

	StringSource(
		key,
		sizeof(key),
		true,
		new HexEncoder(
			new FileSink((filename + "_encoded_key.txt").c_str())
		)
	);

	CFB_Mode<AES>::Decryption Decryptor(key, sizeof(key), iv);
	FileSource(
		(filename + "_encoded.txt").c_str(),
		true,
		new StreamTransformationFilter(
			Decryptor,
			new FileSink((filename + "_decoded.txt").c_str())
		)
	);
}

constexpr auto RSA_KEY_LENGTH = 1024;

void cryptoppexample::asymmetric_chipher_dechipher(std::string filename)
{
	AutoSeededRandomPool rng(true);
	RSA::PrivateKey privateKey;
	privateKey.GenerateRandomWithKeySize(rng, RSA_KEY_LENGTH);
	RSA::PublicKey publicKey(privateKey);

	std::string publicExpString(publicKey.GetPublicExponent().MinEncodedSize(), '\0');
	publicKey.GetPublicExponent().Encode((byte*)publicExpString.c_str(), publicExpString.size());
	StringSource(
		publicExpString,
		true,
		new HexEncoder(
			new FileSink((filename + "_encoded_publicExp.txt").c_str())
		)
	);

	std::string privateExpString(privateKey.GetPrivateExponent().MinEncodedSize(), '\0');
	privateKey.GetPrivateExponent().Encode((byte*)privateExpString.c_str(), privateExpString.size());
	StringSource(
		privateExpString,
		true,
		new HexEncoder(
			new FileSink((filename + "_encoded_privateExp.txt").c_str())
		)
	);

	std::string modulusString(publicKey.GetModulus().MinEncodedSize(), '\0');
	publicKey.GetModulus().Encode((byte*)modulusString.c_str(), modulusString.size());
	StringSource(
		modulusString,
		true,
		new HexEncoder(
			new FileSink((filename + "_encoded_modulus.txt").c_str())
		)
	);

	RSAES_OAEP_SHA_Encryptor Encryptor(publicKey);
	FileSource(
		filename.c_str(),
		true,
		new PK_EncryptorFilter(
			rng,
			Encryptor,
			new FileSink((filename + "_encoded.txt").c_str())
		)
	);

	RSAES_OAEP_SHA_Decryptor Decryptor(privateKey);
	FileSource(
		(filename + "_encoded.txt").c_str(),
		true,
		new PK_DecryptorFilter(
			rng,
			Decryptor,
			new FileSink((filename + "_decoded.txt").c_str())
		)
	);
}

void cryptoppexample::signer_verifier(std::string filename)
{
	AutoSeededRandomPool rng(true);
	RSA::PrivateKey privateKey;
	privateKey.GenerateRandomWithKeySize(rng, RSA_KEY_LENGTH);
	RSA::PublicKey publicKey(privateKey);

	std::string message, signature, recovered;

	FileSource(
		filename.c_str(),
		true,
		new StringSink(message)
	);

	RSASS<PSS, SHA256>::Signer Signer(privateKey);
	StringSource(
		message,
		true,
		new SignerFilter(
			rng,
			Signer,
			new StringSink(signature)
		)
	);

	StringSource(
		signature,
		true,
		new FileSink((filename + "_signature.txt").c_str())
	);

	RSASS<PSS, SHA256>::Verifier Verifier(publicKey);

	try {
		StringSource(
			message + signature,
			true,
			new SignatureVerificationFilter(
				Verifier,
				new StringSink(recovered),
				SignatureVerificationFilter::THROW_EXCEPTION |
				SignatureVerificationFilter::PUT_MESSAGE
			)
		);

		StringSource(
			"good",
			true,
			new FileSink((filename + "_recovered.txt").c_str())
		);

		StringSource(
			message + "baaaaad" + signature,
			true,
			new SignatureVerificationFilter(
				Verifier,
				new StringSink(recovered),
				SignatureVerificationFilter::THROW_EXCEPTION |
				SignatureVerificationFilter::PUT_MESSAGE
			)
		);
	}
	catch (...) {
		StringSource(
			"bad",
			true,
			new FileSink((filename + "_badrecovered.txt").c_str())
		);

	}
}

void cryptoppexample::hash_file(std::string filename)
{
	SHA256 hash;
	std::string message;
	FileSource(
		filename.c_str(),
		true,
		new StringSink(message)
	);

	StringSource(message, true,
		new HashFilter(hash,
			new HexEncoder(new FileSink((filename + "_hash.txt").c_str()))
		)
	);
}
