#pragma once

namespace interface_form {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: interface_ad::interface_adControl^  interface_adControl1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->interface_adControl1 = (gcnew interface_ad::interface_adControl());
			this->SuspendLayout();
			// 
			// interface_adControl1
			// 
			this->interface_adControl1->BackColor = System::Drawing::SystemColors::Window;
			this->interface_adControl1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->interface_adControl1->Location = System::Drawing::Point(12, 12);
			this->interface_adControl1->Name = L"interface_adControl1";
			this->interface_adControl1->Size = System::Drawing::Size(442, 455);
			this->interface_adControl1->TabIndex = 0;
			this->interface_adControl1->Load += gcnew System::EventHandler(this, &Form1::interface_adControl1_Load);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(466, 478);
			this->Controls->Add(this->interface_adControl1);
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Simulador";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void interface_adControl1_Load(System::Object^  sender, System::EventArgs^  e) {

			 }
	};
}

