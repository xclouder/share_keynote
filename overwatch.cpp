










void PlayerConnectionSystem::Update(f32 timeStep)
{
    for (ConnectionComponent* c: ComponentItr<ConnectionComponent>(m_admin))
    {
        InputStreamComponent* is = c->Sibling<InputStreamComponent>();
        StatsComponent* stats = c->Sibling<StatusComponent>();

        if (is->m_inputThisFrame || stats->m_didSomethingCoolLately)
        {
            c->m_afkTimer = 0.0f;               //AFK, away from keyboard
            c->m_sentAFKMessage = false;
        }
        else
        {
            c->m_afkTimer += timeStep;
            if (!c->m_sentAFKMessage && c->m_afkTimer > AFK_MESSAGE_SECONDS)
            {
                c->m_sentAFKMessage = true;
                ConnectionUtil::SendMessage(c->m_connetionHandle, "Move scrub!");
            }
        }
    }
}



