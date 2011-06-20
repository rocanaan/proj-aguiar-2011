#pragma once
#include <vector>
#include <deque>
#include <fstream>
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace std;
double inversa2(double taxa)
{
	return (-1) * (log(1 - GeradorNumerosAleatorios::GetInstance()->Random()) / taxa);
}

int n_clientes;


namespace interface_ad {

	
	void add_up(String ^texto, System::Windows::Forms::TextBox ^textbox)
	{
		String ^temp;
		temp = temp->Copy(textbox->Text);
		
		textbox->Text = texto;
		textbox->Text += "\r\n";
		textbox->Text = textbox->Text->Insert(textbox->Text->Length,temp);

	}
	/// <summary>
	/// Summary for interface_adControl
	/// </summary>
	public ref class interface_adControl : public System::Windows::Forms::UserControl
	{
	public:
		interface_adControl(void)
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
		~interface_adControl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

	private:
		vector<Cliente> *clientes_fila1;
		deque<Cliente*> *clientes_fila2;
		Cliente *cliente_em_servico;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;

			 /// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(interface_adControl::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Location = System::Drawing::Point(401, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(30, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"0";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(356, 257);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Pr�ximo";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &interface_adControl::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(3, 139);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 95);
			this->listBox1->TabIndex = 2;
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Location = System::Drawing::Point(159, 3);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(120, 95);
			this->listBox2->TabIndex = 3;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(185, 158);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(62, 57);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(129, 176);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(50, 25);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(204, 104);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(25, 48);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 6;
			this->pictureBox3->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(201, 176);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(85, 257);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(112, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Pr�xima chegada em: ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(194, 257);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(253, 176);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(97, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Tempo de Servi�o:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(353, 176);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(13, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"0";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(3, 299);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(433, 150);
			this->textBox1->TabIndex = 12;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &interface_adControl::textBox1_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(4, 280);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 13);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Console";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(360, 3);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(40, 13);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Tempo";
			// 
			// interface_adControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"interface_adControl";
			this->Size = System::Drawing::Size(434, 452);
			this->Load += gcnew System::EventHandler(this, &interface_adControl::interface_adControl_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

				 double intervalo = 0.1;
				 srand(time(NULL));
				 double tempo = System::Double::Parse(this->label1->Text);
				 double proxima_chegada;
				 double chegada_atual = System::Double::Parse(this->label4->Text);
				 tempo += intervalo;
				 double taxa_chegada = 1;
				 double taxa_servico = 2;
				 String ^texto;
				 texto += tempo.ToString();
				 texto += " - ";/*
				 textBox1->Text += tempo.ToString();
				 textBox1->Text += " - ";*/
				 if (cliente_em_servico != NULL)	//Se tiver alguem sendo servido
				 {
					 texto += "H� cliente no servidor - ";
					 //textBox1->Text += "Tem alguem sendo servido,  ";	
					 cliente_em_servico->tempo_servico(cliente_em_servico->tempo_servico() - intervalo);
					 label6->Text = cliente_em_servico->tempo_servico().ToString();
					
					 if (cliente_em_servico->tempo_servico() < 0)	//Se o servico acabou
					 {
						 texto += "Servi�o acabou -  ";
					//	 add_up("Servi�o acabou,  ",textBox1);
					//	 textBox1->Text += "Servi�o acabou,  ";	
						 if (cliente_em_servico->tipo_servico() == 2)	//Se o cliente tiver vindo da fila 2
						 {
							 texto += "Cliente veio da fila 2 e est� saindo do sistema - ";
					//		 add_up("O cara veio da fila 2 e vai pro limbo,  ",textBox1);
					//		 textBox1->Text += "O cara veio da fila 2 e vai pro limbo,  ";	
							 delete(cliente_em_servico);
							
						 }
						 else
						 {
							 texto += "Cliente vindo da fila 1 e indo para fila 2 - ";
						//	 add_up("O cara veio da fila 1 e vai pra fila 2,  ",textBox1);
						//	 textBox1->Text += "O cara veio da fila 1 e vai pra fila 2,  ";	
							 listBox2->Items->Add(cliente_em_servico->id().ToString());
							 listBox2->SetSelected(0,true);
							 clientes_fila2->push_back(new Cliente(cliente_em_servico->id(),taxa_servico));
							 clientes_fila2->at(clientes_fila2->size()-1)->tipo_servico(2);
							 textBox1->Text += clientes_fila2->at(0)->id().ToString();
						 }
						 cliente_em_servico = NULL;
						 label6->Text = "0";
						 label2->Text = "0";

						
					 }
				 }
				 Cliente *novocliente;
				 if (tempo >= chegada_atual)
				 {
					 texto += "Aconteceu uma chegada de cliente para fila 1 - ";
			//		 add_up("Chegou gente,  ",textBox1);
			//		 textBox1->Text += "Chegou gente,  ";	
					 n_clientes++;
					 novocliente = new Cliente(n_clientes,taxa_servico);
					
					 clientes_fila1->push_back(*novocliente);
					
					 proxima_chegada = tempo + inversa2(taxa_chegada);
					 label4->Text = proxima_chegada.ToString();
					 
					 listBox1->Items->Add(novocliente->id());
					  
					 listBox1->SetSelected(0,true);
					
				 }
				
				 if (clientes_fila2->empty() == false)	//Se a fila 2 nao estiver vazia
				 {
					texto += "H� clientes na fila 2 - ";
			//		add_up("Fila 2 n�o est� vazia,  ",textBox1);
			//		textBox1->Text += "Fila 2 n�o est� vazia,  ";	
					if (cliente_em_servico == NULL)	//Se nao tiver ninguem sendo servido 								
					{
						texto += "N�o h� ninguem no servidor - ";
				//		add_up("N�o tem ninguem sendo servido,  ",textBox1);
		//				textBox1->Text += "N�o tem ninguem sendo servido,  ";	
						cliente_em_servico = new Cliente(clientes_fila2->at(0)->id(),taxa_servico);
						cliente_em_servico->tempo_servico(clientes_fila2->at(0)->tempo_servico());
						cliente_em_servico->tipo_servico(clientes_fila2->at(0)->tipo_servico());
						label2->Text = cliente_em_servico->id().ToString();
						listBox2->Items->RemoveAt(0);
						label6->Text = cliente_em_servico->tempo_servico().ToString();
						clientes_fila2->erase(clientes_fila2->begin());
					}
				 }

				 if (clientes_fila1->empty() == false)	//Se a fila 1 nao estiver vazia
				 {
					texto += "H� clientes na fila 1 - ";
		//			add_up("Tem gente na fila 1,  ",textBox1);
		//			textBox1->Text += "Tem gente na fila 1,  ";	
					if (cliente_em_servico == NULL)	//Se nao tiver ninguem sendo servido 								
					{
						texto += "N�o h� ninguem no servidor - ";
		//				add_up("Tem ninguem sendo servido,  ",textBox1);
		//				textBox1->Text += "Tem ninguem sendo servido,  ";	
						cliente_em_servico = new Cliente(clientes_fila1->at(0).id(),taxa_servico);
						cliente_em_servico->tempo_servico(clientes_fila1->at(0).tempo_servico());
						label2->Text = cliente_em_servico->id().ToString();
						listBox1->Items->RemoveAt(0);
						label6->Text = cliente_em_servico->tempo_servico().ToString();
						clientes_fila1->erase(clientes_fila1->begin());
					}
					else if (cliente_em_servico->tipo_servico() == 2)	// Se tiver alguem da fila 2 sendo servido
					{
						texto += "H� um cliente que veio da fila 2 no servidor - ";
			//			add_up("Tem um cara da fila 2 sendo servido,  ",textBox1);
			//			textBox1->Text += "Tem um cara da fila 2 sendo servido,  ";	
						clientes_fila2->push_front(cliente_em_servico);
						listBox2->Items->Insert(0,cliente_em_servico->id().ToString()); //vai adicionar ao final.tenho q adicionar ao inicio
						listBox2->SetSelected(0,true);
						cliente_em_servico = new Cliente(clientes_fila1->at(0).id(),taxa_servico);
						cliente_em_servico->tempo_servico(clientes_fila1->at(0).tempo_servico());
						label2->Text = cliente_em_servico->id().ToString();
						listBox1->Items->RemoveAt(0);
						label6->Text = cliente_em_servico->tempo_servico().ToString();
						clientes_fila1->erase(clientes_fila1->begin());
					}
					
				 }

				 add_up(texto,textBox1);
			//	 textBox1->Text += "\r\n";
		//		 textBox1->Select(0,20);
				 this->label1->Text = tempo.ToString();
			 }
	private: System::Void interface_adControl_Load(System::Object^  sender, System::EventArgs^  e) {
				
				 srand(time(NULL));
				 double taxa = 1;
				 n_clientes = 0;
				 double proxima_chegada = inversa2(taxa);
				 this->label2->Text = "0";
				 clientes_fila1 = new vector<Cliente>;
				 clientes_fila2 = new deque<Cliente*>;
				 this->label4->Text = proxima_chegada.ToString();
				
			 }

private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
};

}
