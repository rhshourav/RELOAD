Public Class TextConverter
    Private Sub TextConverter_Load(sender As Object, e As EventArgs) Handles Me.Load
        chkBox_Rem_comments.Checked = True
        ChkBox_Rem_Empty.Checked = True
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim EndText As String
        Dim StartText As String
        Dim pos As Int16 = -1

        Me.txtOutput.Text = ""
        If ChkBox_Add_Linefeed.Checked Then
            EndText = " \r\n""" + ";"
        Else
            EndText = """" + ";"
        End If

        'For Each s As String In Me.txtInput.Lines
        For Z = 0 To txtInput.Lines.Length - 1
            Dim NewLine As String = txtInput.Lines(Z).ToString
            Dim String1 As String = """"
            Dim String2 As String = "\"""
            NewLine = NewLine.Replace(String1, String2)
            If Z = 0 Then StartText = " =" Else StartText = " += " 'First Line only "=" all others "+="
            If chkBox_Rem_comments.Checked Then
                pos = NewLine.IndexOf("//")
                If pos > -1 Then
                    NewLine = NewLine.Substring(0, NewLine.IndexOf("//"))
                End If
            End If
            NewLine = LTrim(NewLine)
            If Not ChkBox_Rem_Empty.Checked Or (ChkBox_Rem_Empty.Checked And NewLine <> "") Then
                Me.txtOutput.Text = Me.txtOutput.Text & "  " & Me.txtVariable.Text & StartText & """" & NewLine & EndText & vbCrLf
            End If

            If ChkBox_copy.Checked Then CopyToClip()
        Next
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        CopyToClip()
    End Sub

    Public Sub CopyToClip()
        Clipboard.Clear()
        Clipboard.SetText(txtOutput.Text)
    End Sub

    Private Sub chkBox_Rem_comments_CheckedChanged(sender As Object, e As EventArgs) Handles chkBox_Rem_comments.CheckedChanged
        If Not chkBox_Rem_comments.Checked And Not ChkBox_Add_Linefeed.Checked Then
            MsgBox("If you allow comments in the output, select the Option 'Add Linefeed (\r\n)'" & vbCrLf &
            "otherwise the result will not work ")
        End If
    End Sub

    Private Sub ChkBox_Add_Linefeed_CheckedChanged(sender As Object, e As EventArgs) Handles ChkBox_Add_Linefeed.CheckedChanged
        If Not chkBox_Rem_comments.Checked And Not ChkBox_Add_Linefeed.Checked Then
            MsgBox("If you allow comments in the output, select the Option 'Add Linefeed (\r\n)'" & vbCrLf &
            "otherwise the result will not work ")
        End If
    End Sub

    Private Sub btnClear_Click(sender As Object, e As EventArgs) Handles btnClear.Click
        Me.txtInput.Text = ""
    End Sub
End Class
