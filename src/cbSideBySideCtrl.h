#ifndef CBSIDEBYSIDECTRL_H
#define CBSIDEBYSIDECTRL_H

#include "cbDiffCtrl.h"

class LineChangedTimer;
class cbStyledTextCtrl;
class cbEditor;

class cbSideBySideCtrl : public cbDiffCtrl
{
public:
    cbSideBySideCtrl(cbDiffEditor *parent);
    virtual ~cbSideBySideCtrl();
    virtual void Init(cbDiffColors colset) override;
    virtual void ShowDiff(wxDiff diff) override;
    void Synchronize();
    void SynchronizeSelection();
    void SynchronizeCaretline();
    void SynchronizeZoom();
    void SynchronizeScroll();

    virtual void NextDifference()override;
    virtual bool CanGotoNextDiff()override;
    virtual void PrevDifference()override;
    virtual bool CanGotoPrevDiff()override;
    virtual void FirstDifference()override;
    virtual bool CanGotoFirstDiff()override;
    virtual void LastDifference()override;
    virtual bool CanGotoLastDiff()override;

    virtual void CopyToLeft()override;
    virtual bool CanCopyToLeft()override;
    virtual void CopyToRight()override;
    virtual bool CanCopyToRight()override;
    virtual void CopyToLeftNext()override;
    virtual bool CanCopyToLeftNext()override;
    virtual void CopyToRightNext()override;
    virtual bool CanCopyToRightNext()override;

    virtual bool GetModified() const override;
    virtual bool QueryClose() override;
    virtual bool Save() override;

    virtual void Undo()override;
    virtual void Redo()override;
    virtual void ClearHistory()override;
    virtual void Cut()override;
    virtual void Copy()override;
    virtual void Paste()override;
    virtual bool CanUndo() const override;
    virtual bool CanRedo() const override;
    virtual bool HasSelection() const override;
    virtual bool CanPaste() const override;
    virtual bool CanSelectAll() const override;
    virtual void SelectAll() override;
protected:
    virtual bool LeftModified() override;
    virtual bool RightModified() override;
private:
    void selectDiffRight(long line);
    void markSelectionDiffRight(long line);
    void unmarkSelectionDiffRight();
    void markSelectionEmptyPartRight(long line);
    void selectDiffLeft(long line);
    void markSelectionDiffLeft(long line);
    void unmarkSelectionDiffLeft();
    void markSelectionEmptyPartLeft(long line);
    void DeleteMarksForSelectionLeft();
    void DeleteMarksForSelectionRight();

    cbEditor *GetCbEditorIfActive(const wxString &filename);

    int lastSyncedLine_;
    int lastSyncedLHandle_;
    int lastSyncedRHandle_;
    long lastLeftMarkedDiff_;
    long lastRightMarkedDiff_;
    long lastLeftMarkedEmptyDiff_;
    long lastRightMarkedEmptyDiff_;
    void OnEditorChange(wxScintillaEvent &event);
    bool SaveLeft();
    bool SaveRight();
    cbStyledTextCtrl *tcLeft_;
    cbStyledTextCtrl *tcRight_;

    wxScrollBar *vScrollBar_;
    wxScrollBar *hScrollBar_;

    struct Block
    {
        Block():len(0),empty(0), ref(0){}
        int len;
        int empty;
        long ref;
    };
    std::vector<long> linesRightWithDifferences_;
    std::map<long, Block> rightChanges_;
    std::vector<long> linesLeftWithDifferences_;
    std::map<long, Block> leftChanges_;

    int lineNumbersWidthLeft_;
    int lineNumbersWidthRight_;
    void doCopyToLeft(const Block &leftBlock, const Block &rightBlock);
    void doCopyToRight(const Block &leftBlock, const Block &rightBlock);

    static void setLineNumberMarginWidth(cbStyledTextCtrl *stc, int &currWidth);

    int vscrollpos_;
    int hscrollpos_;

    LineChangedTimer *timer_;
    DECLARE_EVENT_TABLE()
};

#endif
