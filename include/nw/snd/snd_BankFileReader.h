#ifndef NW_SND_BANK_FILE_READER_H_
#define NW_SND_BANK_FILE_READER_H_

#include <nw/snd/snd_Global.h>
#include <nw/snd/snd_BankFile.h>

namespace nw { namespace snd { namespace internal {

struct VelocityRegionInfo
{
    u32 waveArchiveId;
    u32 waveIndex;

    f32 pitch;
    AdshrCurve adshrCurve;

    u8 originalKey;
    u8 volume;
    u8 pan;
    bool isIgnoreNoteOff;
    u8 keyGroup;
    u8 interpolationType;
};
static_assert(sizeof(VelocityRegionInfo) == 0x18);

class BankFileReader
{
public:
    static const u32 SIGNATURE_FILE = NW_UT_MAKE_SIGWORD('F', 'B', 'N', 'K');

    BankFileReader();
    explicit BankFileReader(const void* bankFile);
    void Initialize(const void* bankFile);
    void Finalize();

    bool IsInitialized() const { return m_IsInitialized; }

    bool ReadVelocityRegionInfo(
        VelocityRegionInfo* info,
        int programNo,
        int key,
        int velocity
    ) const;

    /*
    // TODO
    const Util::WaveIdTable* GetWaveIdTable() const;
    */
    const void* GetBankFileAddress() const { return m_pHeader; }

    /*
    // TODO
    int GetInstrumentCount() const
    {
        if (m_IsInitialized == false)
            return 0;

        return m_pInfoBlockBody->GetInstrumentCount();
    }
    */

private:
    const BankFile::FileHeader*     m_pHeader;
    const BankFile::InfoBlockBody*  m_pInfoBlockBody;
    bool m_IsInitialized;
};
static_assert(sizeof(BankFileReader) == 0xC);

} } } // namespace nw::snd::internal

#endif // NW_SND_BANK_FILE_READER_H_
