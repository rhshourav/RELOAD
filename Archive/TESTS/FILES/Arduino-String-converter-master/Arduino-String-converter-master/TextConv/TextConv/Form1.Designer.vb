<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class TextConverter
    Inherits System.Windows.Forms.Form

    'Das Formular überschreibt den Löschvorgang, um die Komponentenliste zu bereinigen.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Wird vom Windows Form-Designer benötigt.
    Private components As System.ComponentModel.IContainer

    'Hinweis: Die folgende Prozedur ist für den Windows Form-Designer erforderlich.
    'Das Bearbeiten ist mit dem Windows Form-Designer möglich.  
    'Das Bearbeiten mit dem Code-Editor ist nicht möglich.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.txtInput = New System.Windows.Forms.TextBox()
        Me.txtOutput = New System.Windows.Forms.TextBox()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.txtVariable = New System.Windows.Forms.TextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.ChkBox_copy = New System.Windows.Forms.CheckBox()
        Me.ChkBox_Add_Linefeed = New System.Windows.Forms.CheckBox()
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.ChkBox_Rem_Empty = New System.Windows.Forms.CheckBox()
        Me.chkBox_Rem_comments = New System.Windows.Forms.CheckBox()
        Me.btnClear = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'txtInput
        '
        Me.txtInput.Location = New System.Drawing.Point(12, 45)
        Me.txtInput.Multiline = True
        Me.txtInput.Name = "txtInput"
        Me.txtInput.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.txtInput.Size = New System.Drawing.Size(436, 621)
        Me.txtInput.TabIndex = 0
        '
        'txtOutput
        '
        Me.txtOutput.Location = New System.Drawing.Point(709, 45)
        Me.txtOutput.Multiline = True
        Me.txtOutput.Name = "txtOutput"
        Me.txtOutput.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.txtOutput.Size = New System.Drawing.Size(436, 621)
        Me.txtOutput.TabIndex = 1
        '
        'Button1
        '
        Me.Button1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button1.Location = New System.Drawing.Point(504, 304)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(126, 61)
        Me.Button1.TabIndex = 2
        Me.Button1.Text = "Go! -->"
        Me.ToolTip1.SetToolTip(Me.Button1, "Convert")
        Me.Button1.UseVisualStyleBackColor = True
        '
        'txtVariable
        '
        Me.txtVariable.Location = New System.Drawing.Point(504, 160)
        Me.txtVariable.Name = "txtVariable"
        Me.txtVariable.Size = New System.Drawing.Size(75, 20)
        Me.txtVariable.TabIndex = 3
        Me.txtVariable.Text = "HTMLstring"
        Me.ToolTip1.SetToolTip(Me.txtVariable, "Name of the string variable in the output")
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(585, 163)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(71, 13)
        Me.Label1.TabIndex = 4
        Me.Label1.Text = "Stringvariable"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(431, 18)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(293, 13)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "Converts HTML, CSS, JavaScript to Variable for Arduino IDE"
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(504, 511)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(126, 23)
        Me.Button2.TabIndex = 6
        Me.Button2.Text = "Copy to Clipboard"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'ChkBox_copy
        '
        Me.ChkBox_copy.AutoSize = True
        Me.ChkBox_copy.Location = New System.Drawing.Point(504, 472)
        Me.ChkBox_copy.Name = "ChkBox_copy"
        Me.ChkBox_copy.Size = New System.Drawing.Size(172, 17)
        Me.ChkBox_copy.TabIndex = 7
        Me.ChkBox_copy.Text = "Copy to Clipboard after convert"
        Me.ChkBox_copy.UseVisualStyleBackColor = True
        '
        'ChkBox_Add_Linefeed
        '
        Me.ChkBox_Add_Linefeed.AutoSize = True
        Me.ChkBox_Add_Linefeed.Location = New System.Drawing.Point(504, 197)
        Me.ChkBox_Add_Linefeed.Name = "ChkBox_Add_Linefeed"
        Me.ChkBox_Add_Linefeed.Size = New System.Drawing.Size(120, 17)
        Me.ChkBox_Add_Linefeed.TabIndex = 8
        Me.ChkBox_Add_Linefeed.Text = "Add Linefeed (\r\n) "
        Me.ToolTip1.SetToolTip(Me.ChkBox_Add_Linefeed, "Add Linefeed at the end of each output line.  Must be checked if //comments ar us" &
        "ed in the Output!")
        Me.ChkBox_Add_Linefeed.UseVisualStyleBackColor = True
        '
        'ToolTip1
        '
        Me.ToolTip1.BackColor = System.Drawing.Color.LightSalmon
        '
        'ChkBox_Rem_Empty
        '
        Me.ChkBox_Rem_Empty.AutoSize = True
        Me.ChkBox_Rem_Empty.Location = New System.Drawing.Point(504, 231)
        Me.ChkBox_Rem_Empty.Name = "ChkBox_Rem_Empty"
        Me.ChkBox_Rem_Empty.Size = New System.Drawing.Size(126, 17)
        Me.ChkBox_Rem_Empty.TabIndex = 9
        Me.ChkBox_Rem_Empty.Text = "Remove Empty Lines"
        Me.ToolTip1.SetToolTip(Me.ChkBox_Rem_Empty, "Remove all empty lines in the output")
        Me.ChkBox_Rem_Empty.UseVisualStyleBackColor = True
        '
        'chkBox_Rem_comments
        '
        Me.chkBox_Rem_comments.AutoSize = True
        Me.chkBox_Rem_comments.Location = New System.Drawing.Point(504, 268)
        Me.chkBox_Rem_comments.Name = "chkBox_Rem_comments"
        Me.chkBox_Rem_comments.Size = New System.Drawing.Size(118, 17)
        Me.chkBox_Rem_comments.TabIndex = 10
        Me.chkBox_Rem_comments.Text = "Remove Comments"
        Me.ToolTip1.SetToolTip(Me.chkBox_Rem_comments, "Remove all //Comments")
        Me.chkBox_Rem_comments.UseVisualStyleBackColor = True
        '
        'btnClear
        '
        Me.btnClear.Location = New System.Drawing.Point(176, 13)
        Me.btnClear.Name = "btnClear"
        Me.btnClear.Size = New System.Drawing.Size(67, 23)
        Me.btnClear.TabIndex = 11
        Me.btnClear.Text = "Clear"
        Me.btnClear.UseVisualStyleBackColor = True
        '
        'TextConverter
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1158, 683)
        Me.Controls.Add(Me.btnClear)
        Me.Controls.Add(Me.chkBox_Rem_comments)
        Me.Controls.Add(Me.ChkBox_Rem_Empty)
        Me.Controls.Add(Me.ChkBox_Add_Linefeed)
        Me.Controls.Add(Me.ChkBox_copy)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.txtVariable)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.txtOutput)
        Me.Controls.Add(Me.txtInput)
        Me.Name = "TextConverter"
        Me.Text = "TextConverter"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents txtInput As TextBox
    Friend WithEvents txtOutput As TextBox
    Friend WithEvents Button1 As Button
    Friend WithEvents txtVariable As TextBox
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents Button2 As Button
    Friend WithEvents ChkBox_copy As CheckBox
    Friend WithEvents ChkBox_Add_Linefeed As CheckBox
    Friend WithEvents ToolTip1 As ToolTip
    Friend WithEvents ChkBox_Rem_Empty As CheckBox
    Friend WithEvents chkBox_Rem_comments As CheckBox
    Friend WithEvents btnClear As Button
End Class
