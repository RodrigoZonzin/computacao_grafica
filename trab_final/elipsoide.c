void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC){
	float tStep = (Pi) / (float)uiSlices;
	float sStep = (Pi) / (float)uiStacks;
	
	//Essa linha desenha em modo wireframe, caso queiram ver os polígonos criados pela função
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for(float t = -Pi/2; t <= (Pi/2)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -Pi; s <= Pi+.0001; s += sStep)
		{
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
}    
