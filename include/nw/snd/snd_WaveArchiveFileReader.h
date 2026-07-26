#ifndef NW_SND_WAVE_ARCHIVE_FILE_READER_H_
#define NW_SND_WAVE_ARCHIVE_FILE_READER_H_

#include <nw/snd/snd_WaveArchiveFile.h>

namespace nw { namespace snd { namespace internal {

class WaveArchiveFileReader
{
public:
    static const u32 SIGNATURE_FILE = NW_UT_MAKE_SIGWORD('F', 'W', 'A', 'R');
    static const u32 SIGNATURE_WARC_TABLE /* = NW_UT_MAKE_SIGWORD('F', 'W', 'A', 'T') */;

    WaveArchiveFileReader(const void* pWaveArchiveFile, bool isIndividual = false);
    WaveArchiveFileReader();
    void Initialize(const void* warcFile, bool isIndividual = false);
    void Finalize();

    void InitializeFileTable();
    bool IsAvailable() const { return m_pHeader != NULL; }

    u32 GetWaveFileCount() const;
    u32 GetWaveFileSize(u32 waveIndex) const;
    u32 GetWaveFileOffsetFromFileHead(u32 waveIndex) const;

    const void* GetWaveFile(u32 waveIndex) const;

    const void* SetWaveFile(u32 waveIndex, const void* pWaveFile);
    bool IsLoaded(u32 waveIndex) const
    {
        if (m_IsInitialized == false)
            return false;
        if (GetWaveFile(waveIndex) != NULL)
            return true;
        return false;
    }

    bool HasIndividualLoadTable() const;

private:
    struct IndividualLoadTable
    {
        const void* waveFile[1];
    };

    /*
    // TODO
    const void* GetWaveFileForWhole(u32 waveIndex) const
    {
        u32 offset = m_pInfoBlockBody->GetOffsetFromFileBlockBody(waveIndex);
        return ut::AddOffsetToPtr(&m_pHeader->GetFileBlock()->body, offset);
    }
    */
    const void* GetWaveFileForIndividual(u32 waveIndex) const
    {
        return m_pLoadTable->waveFile[ waveIndex ];
    }

    const WaveArchiveFile::FileHeader*      m_pHeader;
    const WaveArchiveFile::InfoBlockBody*   m_pInfoBlockBody;
    IndividualLoadTable*                    m_pLoadTable;
    bool m_IsInitialized;
};

} } } // namespace nw::snd::internal

#endif // NW_SND_WAVE_ARCHIVE_FILE_READER_H_
